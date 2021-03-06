#include "Minimax.h"
#include "gameDef.h"
#include "gameUtil.h"

#include <QDebug>

using std::vector;
using std::max;
using std::min;

static bool DEBUG = false;

namespace agent{

Minimax::Minimax(char mark, bool randomForTie)
    :Agent(mark), random_(randomForTie)
{
    tieBreaker_.setInitVal(-INF);
}

Minimax::~Minimax()
{}

bool Minimax::approxEqual(double f1, double f2, double epsilon)
{
    double diff = ((f1 - f2)>0)?(f1 - f2):((f1 - f2)*-1);
    return diff < epsilon;
}


int Minimax::move(const char* state)
{
    game::NextStates nextStates(selfMark_, state);

    double best = -INF;
    int bestPos = -1;

    for(std::size_t i =0; i < nextStates.size(); ++i){
        char* futState = nextStates.at(i);
        int pos = (int)futState[game::BOARD_SIZE];
        double val = minimax(futState, MAX_DEPTH-1, false);

        if(DEBUG) qDebug() << "pos:" << pos << ", val:" << val;

        if(random_){
            tieBreaker_.add(pos, val);
            continue;
        }

        if( val > best){
            best = val;
            bestPos = pos;
        }
    }

    if(random_){
        bestPos = tieBreaker_.getBestPos();
        tieBreaker_.reset();

    }

    if(DEBUG) qDebug() << "best pos:" << bestPos << "\n";

    return bestPos;
}


double Minimax::minimax(const char* state, int depth, bool isMax)
{
    double centerAdj = 0;
    if(state[4]== selfMark_)
        centerAdj = CENTER_ADJ;
    else if(state[4] == opponentMark_)
        centerAdj = -CENTER_ADJ;

    if(game::isWon(state,selfMark_)){
        return WIN + depth*DEPTH_ADJ + centerAdj;
    }
    if(game::isWon(state,opponentMark_)){
        return LOSE - depth*DEPTH_ADJ + centerAdj;
    }
    if(game::isFull(state) || depth == 0){
        return DRAW + centerAdj;
    }

    char mark = isMax?selfMark_:opponentMark_;
    game::NextStates nextStates(mark, state);
    std::size_t size = nextStates.size();
    double best;

    if(isMax){
        best = -INF;
        for(std::size_t idx = 0; idx < size; ++idx)
            best = max(best, minimax(nextStates.at(idx), depth-1, false));
    }else{
        best = INF;
        for(std::size_t idx = 0; idx < size; ++idx)
            best = min(best, minimax(nextStates.at(idx), depth-1, true));
    }

    return best;
}


}


/* test case:
 *
 *  //depth testing, ai:o
    //gameInstance.loadBoard("~x~~~xoox");
 */
