#include "qLearning.h"
#include "../gameDef.h"
#include "../gameUtil.h"
#include "util/runtimeEx.h"
#include "util/random.h"
#include "io/simpleWriter.h"
#include "io/simpleReader.h"
#include "tieBreaker.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include <qDebug>
#include "io/jsonReader.h"

using namespace game;

using std::vector;
using std::string;




namespace agent{


bool QLearning::isInit_ = false;
bool QLearning::isTraining_ = false;

std::string QLearning::dataPath_ = "";

std::unique_ptr<io::Config> QLearning::config_ = nullptr;

game::LookupTable QLearning::lookupTable_;
 
QLearning::QLearning(char mark):Agent(mark)
{
    if(!isInit_){
        config_ = std::make_unique<io::Config>(game::QLEARNING_CONFIG_PATH);

        std::vector< std::pair<QString, QString> > vec = {
            {QLEARNING_TRAINING_MODE,"off"},
            {QLEARNING_LOAD_TRAINING_DATA_ON_START,"on"}
        };

        config_->initialize(vec);

        isTraining_ = config_->get<bool>(QLEARNING_TRAINING_MODE);

        bool loadData = config_->get<bool>(QLEARNING_LOAD_TRAINING_DATA_ON_START);

        if(loadData){
            dataPath_ = (config_->get<QString>(QLEARNING_TRAINING_DATA_PATH)).toStdString();

            if(io::SimpleReader::canBeOpen(dataPath_)){
                lookupTable_.loadData(dataPath_);
            }else{
                std::stringstream ss;
                ss << dataPath_ << " cannot be open; start QLearning anyway";
                qDebug() << ss.str().c_str();
            }

        }

        isInit_ = true;
    }
}

QLearning::~QLearning()
{
    if(isInit_){
        if(isTraining_ || config_->get<bool>(QLEARNING_SAVE_TRAINING_DATA)){
            auto writer = std::make_shared<io::SimpleWriter>(dataPath_, 200000, false);

            //currently it is simple overwritten - do we want to change in the future?
            lookupTable_.saveData(writer);
            qDebug() << "writing qLearning.dat done" ;
        }
        isInit_ = false;
    }
}


bool QLearning::leftBetterThanRight(double lhs, double rhs, char mark)
{
    if(mark == MARK_X)
        return lhs > rhs;
    else if(mark == MARK_O)
        return lhs < rhs;
    else
        THROW_RUNTIME_EX("invalid mark!");
}


int QLearning::move(const char* state)
{
    if(isTraining_) {
        return trainMove(state);
    }
	
    game::NextStates nextStates(selfMark_, state);

    double initBestVal = (selfMark_ == MARK_X)?(-INF):(INF);

    tieBreaker_.setInitVal(initBestVal);

    for(unsigned int i=0; i<nextStates.size(); ++i){
        char* futState = nextStates.at(i);
        double val;
        int pos = futState[game::BOARD_SIZE];
        if(!lookupTable_.get(futState, val)){
            val = DRAW;
            lookupTable_.set(futState, val);
        }

        tieBreaker_.add(pos, val, selfMark_);
    }
	
    int bestPos = tieBreaker_.getBestPos();
    tieBreaker_.reset();
    return bestPos;
}


/*
Q_t1(s_t, a_t) = Q_t(s_t, a_t) + 
	alpha_t(s_t, a_t) * {R_t1 + gamma * maxQ_t(s_t1, a_t) - Q_t(s_t, a_t)}
*/

double QLearning::qLearning(const char* sa, int a)
{
    double q_t0 = DRAW;

    if(!lookupTable_.get(sa, q_t0)){
        lookupTable_.set(sa, q_t0);
    }

    bool done = false;
    double reward = DRAW;
    if(game::isWon(sa, a)){
        reward = (sa[a] == MARK_X)?X_WIN:O_WIN;
        done = true;
    }
    else if(game::isFull(sa)){
        reward = DRAW;
        done = true;
    }

    if(done){
        return reward;
    }

    // find opponent's best move value
    // if not explored, set to default
    // if explored return the value
    double opponentBest = (selfMark_ == MARK_X)?(INF):(-INF);
    game::NextStates nextStates(game::determineTurn(sa), sa);
    for(size_t idx =0; idx < nextStates.size(); ++idx){
        char* nextState = nextStates.at(idx);
        double val = DRAW;
        if(!lookupTable_.get(nextState, val)){
            lookupTable_.set(nextState, val);
        }
        if(leftBetterThanRight(val, opponentBest, opponentMark_)){
            opponentBest = val;
        }
    }

    double q_t1 = (1-alpha) * q_t0 + alpha * (reward + gamma * opponentBest);

    if(q_t1 < -1 || q_t1 > 1) {
        THROW_RUNTIME_EX("invalid value!");
    }

    return q_t1;
}

int QLearning::trainMove(const char* state)
{
    game::NextStates nextStates(selfMark_, state);

    int action = INVALID;
    int index = 0;

    if(util::Random::uniformReal(0,1) < exploitProb){
        //exploitation
        double best = (selfMark_ == MARK_X)?(-INF):(INF);
        for(unsigned int i =0; i<nextStates.size(); ++i){
            double val = DRAW;
            char* nextState = nextStates.at(i);
            lookupTable_.get(nextState, val); //set later

            if(leftBetterThanRight(val, best, selfMark_)){
                best = val;
                action = nextState[game::BOARD_SIZE];
                index = i;
            }
        }
    }
    else{
        //exploration
        int size = (int)nextStates.size();
        index = util::Random::uniformInt(0, size-1);
        action = (nextStates.at(index))[game::BOARD_SIZE];
    }
	
    char* stateAction = nextStates.at(index);
    double val = qLearning(stateAction, action);
    lookupTable_.set(stateAction, val);


    std::string theState(stateAction, game::BOARD_SIZE+1);
    history_.emplace_back(theState);

    return action;
}

void QLearning::postProcess()
{
    if(isTraining_) {
        //backward propgating the Q value
        for(int idx = history_.size()-1; idx >=0; --idx){
            const char* stateAction = history_.at(idx).c_str();
            int action = stateAction[game::BOARD_SIZE];
            double val = qLearning(stateAction, action);
            lookupTable_.set(stateAction, val);
        }
        history_.clear();
        //qDebug() << "QLearning::postProcess";
    }
}

void QLearning::print()
{
    lookupTable_.print();
}



}//namespace

/*
 * test case
 * ~o~~x~~~~
 */
