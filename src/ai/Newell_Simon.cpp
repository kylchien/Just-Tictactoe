#include "Newell_Simon.h"
#include "../gameDef.h"
#include "../utility.h"
#include <QDebug>

//#define DEBUG_FLAG

#ifdef DEBUG_FLAG
    #define DEBUG(msg) \
        qDebug() << msg;
#else
    #define DEBUG(msg)
#endif

namespace ai{

//initialize class static vector
using Function = std::function<int(Newell_Simon*, const char*)>;
std::vector<Function> Newell_Simon::ruleSet_;

Newell_Simon::Newell_Simon(char mark):Player(mark)
{
    initialize();
}

Newell_Simon::~Newell_Simon()
{}


void Newell_Simon::initialize()
{
    ruleSet_.clear();

    //rule order matter (priority from high to low)
    ruleSet_.push_back(&Newell_Simon::doWin);
    ruleSet_.push_back(&Newell_Simon::doBlockWin);
    ruleSet_.push_back(&Newell_Simon::doFork);
    ruleSet_.push_back(&Newell_Simon::doConnectTwo);
    ruleSet_.push_back(&Newell_Simon::doBlockFork);
    ruleSet_.push_back(&Newell_Simon::doCenter);
    ruleSet_.push_back(&Newell_Simon::doOppositeCorner);
    ruleSet_.push_back(&Newell_Simon::doEmptyCorner);
    ruleSet_.push_back(&Newell_Simon::doEmptySide);
}

int Newell_Simon::move(const char* state)
{
    for(auto rule:ruleSet_){
        int theMove = rule(this,state);
        if(theMove != game::INVALID){
            return theMove;
        }
    }
    return game::INVALID;
}



#define FIND_TWO_CONNECT(state, i, j, k, numX, numO, numE) \
    if(game::matchCount(state, i, j, k, numX, numO, numE)){ \
        return game::getPos(state, game::MARK_E, i, j, k); \
    }

int Newell_Simon::doWin(const char* state)
{
    DEBUG("in doWin");

    int numX = 0, numO = 2, numE = 1;
    if(selfMark_ == game::MARK_X){
        numX = 2;
        numO = 0;
    }

    for(int i=0; i<3; i++){
        FIND_TWO_CONNECT(state, i, i+3, i+6, numX, numO, numE);
        FIND_TWO_CONNECT(state, 3*i, 3*i+1, 3*i+2, numX, numO, numE);
    }
    FIND_TWO_CONNECT(state, 0, 4, 8, numX, numO, numE);
    FIND_TWO_CONNECT(state, 2, 4, 6, numX, numO, numE);

    return game::INVALID;
}

int Newell_Simon::doBlockWin(const char* state)
{
    DEBUG("in doBlock");

    int numX = 0, numO = 2, numE = 1;
    if(opponentMark_ == game::MARK_X){
        numX = 2;
        numO = 0;
    }

    for(int i=0; i<3; i++){
        FIND_TWO_CONNECT(state, i, i+3, i+6, numX, numO, numE);
        FIND_TWO_CONNECT(state, 3*i, 3*i+1, 3*i+2, numX, numO, numE);
    }
    FIND_TWO_CONNECT(state, 0, 4, 8, numX, numO, numE);
    FIND_TWO_CONNECT(state, 2, 4, 6, numX, numO, numE);
    return game::INVALID;
}



int Newell_Simon::doFork(const char* state)
{
    DEBUG("in doFork");

    std::vector<char*> futStates;
    game::allocNextStates(selfMark_, state, futStates);
    for(auto futState : futStates){
        if(game::hasFork(futState, selfMark_))
            return (int)futState[game::BOARD_SIZE];
    }
    game::deallocNextStates(futStates);
    return game::INVALID;
}

int Newell_Simon::doBlockFork(const char* state)
{
    DEBUG("in doBlockFork");

    std::vector<char*> futStates;
    game::allocNextStates(opponentMark_, state, futStates);
    for(auto futState : futStates){
        if(game::hasFork(futState, opponentMark_))
            return (int)futState[game::BOARD_SIZE];
    }
    game::deallocNextStates(futStates);
    return game::INVALID;
}


//check opponent's reaction after setup two-in-a-row
//if opponent cannot use block to create his fork
//the setup is a valid move
#define MAKE_CONNECT_TWO(state, i, j, k, numX, numO, numE) \
    if(game::matchCount(state, i, j, k, numX, numO, numE)){ \
        int emptyPos = game::getPos(state, game::MARK_E, i, j, k); \
        char newState[game::BOARD_SIZE]; \
        game::copyBoard(state, newState); \
        newState[emptyPos] = opponentMark_; \
        if(!game::hasFork(newState, opponentMark_)){ \
            return (int)state[game::BOARD_SIZE]; \
        } \
    }\

int Newell_Simon::doConnectTwo(const char* state)
{
    DEBUG("in doConnectTwo");
    int numX = 0, numO = 2, numE = 1;
    if(selfMark_ == game::MARK_X){
        numX = 2; numO = 0;
    }

    std::vector<char*> futStates;
    game::allocNextStates(selfMark_, state, futStates);
    for(auto futState : futStates){
        for(int i=0; i<3; ++i){
            MAKE_CONNECT_TWO(futState, i, i+3, i+6, numX, numO, numE);
            MAKE_CONNECT_TWO(futState, 3*i, 3*i+1, 3*i+2, numX, numO, numE);
        }
        MAKE_CONNECT_TWO(futState, 0, 4, 8, numX, numO, numE);
        MAKE_CONNECT_TWO(futState, 2, 4, 6, numX, numO, numE);
    }

    game::deallocNextStates(futStates);
    return game::INVALID;
}

int Newell_Simon::doCenter(const char* state)
{
    DEBUG("in doCenter");
    if(state[4] == game::MARK_E)
        return 4;
    return game::INVALID;
}

#define OPPOSITE_CORNER(state, i, j) \
    if(state[i] == opponentMark_ && state[j] == game::MARK_E) \
        return j; \

int Newell_Simon::doOppositeCorner(const char* state)
{
    DEBUG("in doOppositeCorner");
    OPPOSITE_CORNER(state, 0, 8);
    OPPOSITE_CORNER(state, 8, 0);
    OPPOSITE_CORNER(state, 2, 6);
    OPPOSITE_CORNER(state, 6, 2);
    return game::INVALID;
}

#define ASSIGN_POS_RANDOMLY(state, vec, i, j, k, l) \
    if(state[i] == game::MARK_E) vec.push_back(i); \
    if(state[j] == game::MARK_E) vec.push_back(j); \
    if(state[k] == game::MARK_E) vec.push_back(k); \
    if(state[l] == game::MARK_E) vec.push_back(l); \
    if(vec.size() == 1) \
        return vec.at(0); \
    else if(!vec.empty()) \
        return vec.at(util::uniformRand(0,vec.size()-1)); \


int Newell_Simon::doEmptyCorner(const char* state)
{
    DEBUG("in doEmptyCorner");
    std::vector<int> vec;
    ASSIGN_POS_RANDOMLY(state, vec, 0,2,6,8);
    return game::INVALID;
}

int Newell_Simon::doEmptySide(const char* state)
{
    DEBUG("in doEmptySide");
    std::vector<int> vec;
    ASSIGN_POS_RANDOMLY(state, vec, 1,3,5,7);
    return game::INVALID;
}


}//namespace
