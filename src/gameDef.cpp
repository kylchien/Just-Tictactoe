#include "gamedef.h"
#include <cstdlib>
#include <cstring>
#include "ai/ai.h"
#include <QDebug>

namespace game{

char determineTurn(const char* curState)
{
    int count = 0;
    for(int i=0; i<BOARD_SIZE; ++i){
        if(curState[i] == MARK_X)
            count++;
        else if(curState[i] == MARK_O)
            count--;
    }
    return (count==0) ? MARK_X : MARK_O;
}


void copyBoard(const char* src, char* tgt)
{
    std::memcpy(tgt, src, sizeof(char)* BOARD_SIZE);
}


void allocNextStates(char mark, const char* curState, std::vector<char*>& futStates)
{
    for(int i=0; i<BOARD_SIZE; ++i){
        if(curState[i] == MARK_E){
            char* futState = (char*)malloc(sizeof(char)*(BOARD_SIZE+2));
            //std::memcpy(futState, curState, sizeof(char)* BOARD_SIZE);
            copyBoard(curState, futState);

            futState[i] = mark;
            futState[BOARD_SIZE] = (char)i; //record the index
            futState[BOARD_SIZE+1] = '\0';

            futStates.push_back(futState);
        }
    }
}

void deallocNextStates(std::vector<char*>& futStates)
{
    for(auto futState : futStates)
        free(futState);
}

void push3(std::vector<int>& vec, int i, int j, int k)
{
    vec.push_back(i);
    vec.push_back(j);
    vec.push_back(k);
}

/*
Outcome outcome(const char* state, std::vector<int>& winPos)
{
    Outcome o = Outcome::NIL;

    for(int i=0; i<3; ++i){
        //column check
        if(state[i] != MARK_E && state[i] == state[i+3] && state[i] == state[i+6]){
            push3(winPos, i, i+3, i+6);
            o = (state[i] == MARK_X)?(Outcome::XWIN):(Outcome::OWIN);
        }

        //row check
        if(state[3*i] != MARK_E && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2]){
            push3(winPos, 3*i, 3*i+1, 3*i+2);
            o = (state[3*i] == MARK_X)?(Outcome::XWIN):(Outcome::OWIN);
        }
    }
    //diagonal check
    if(state[0] != MARK_E && state[0] == state[4] && state[0] == state[8]){
        push3(winPos, 0,4,8);
        o = (state[0] == MARK_X)?(Outcome::XWIN):(Outcome::OWIN);
    }
    if(state[2] != MARK_E && state[2] == state[4] && state[2] == state[6]){
        push3(winPos, 2,4,6);
        o = (state[2] == MARK_X)?(Outcome::XWIN):(Outcome::OWIN);
    }

    return o;
}*/


bool isWon(const char* state, std::vector<int>& winPos)
{
    for(int i=0; i<3; ++i){
        //column check
        if(state[i] != MARK_E && state[i] == state[i+3] && state[i] == state[i+6]){
            push3(winPos, i, i+3, i+6);
            return true;
        }

        //row check
        if(state[3*i] != MARK_E && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2]){
            push3(winPos, 3*i, 3*i+1, 3*i+2);
            return true;
        }
    }
    //diagonal check
    if(state[0] != MARK_E && state[0] == state[4] && state[0] == state[8]){
        push3(winPos, 0,4,8);
        return true;
    }
    if(state[2] != MARK_E && state[2] == state[4] && state[2] == state[6]){
        push3(winPos, 2,4,6);
        return true;
    }

    return false;
}

bool isWon(const char* state, char mark){
    for(int i=0; i<3; ++i){
        if(state[i] == mark && state[i] == state[i+3] && state[i] == state[i+6])
            return true;
        if(state[3*i] == mark && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2])
            return true;
    }
    if(state[0] == mark && state[0] == state[4] && state[0] == state[8])
        return true;
    if(state[2] == mark && state[2] == state[4] && state[2] == state[6])
        return true;
    return false;
}

bool isFull(const char* state)
{
    for(int i=0; i<BOARD_SIZE; ++i)
        if(state[i] == MARK_E)
            return false;
    return true;
}



inline void count(const char& mark, int& numX, int& numO, int& numE)
{
    if(mark == MARK_X) numX++;
    if(mark == MARK_O) numO++;
    if(mark == MARK_E) numE++;
}

bool matchCount(
    const char* state,
    int i, int j, int k,
    int countX, int countO, int countE)

{
    int numX =0, numO = 0, numE = 0;
    count(state[i], numX, numO, numE);
    count(state[j], numX, numO, numE);
    count(state[k], numX, numO, numE);
    /*
    qDebug() << "in match count:[" << i << j << k << "]";
    qDebug() << "expectX:" << countX << ", actual:" << numX;
    qDebug() << "expectO:" << countO << ", actual:" << numO;
    qDebug() << "expectE:" << countE << ", actual:" << numE;*/
    return numX == countX && numO == countO && numE == countE;
}

int getPos(const char* state, char mark, int i, int j, int k)
{
    if(state[i] == mark) return i;
    if(state[j] == mark) return j;
    if(state[k] == mark) return k;
    return INVALID;
}

bool hasFork(const char* state, char mark)
{
    int numX=0, numO=2, numE=1;
    if(mark == MARK_X){ numX=2; numO=0;}

    int count = 0;
    for(int i=0; i<3; ++i){
        if(matchCount(state, i, i+3, i+6, numX, numO, numE)){
            count++;
            if(count == 2) return true;
        }
        if(matchCount(state, 3*i, 3*i+1, 3*i+2, numX, numO, numE)){
            count++;
            if(count == 2) return true;
        }

    }
    if(matchCount(state, 0, 4, 8, numX, numO, numE)){
        count++;
        if(count == 2) return true;
    }
    if(matchCount(state, 2, 4, 6, numX, numO, numE)){
        count++;
        if(count == 2) return true;
    }
    return false;
}

void rotateCW90(const char* src, char* target)
{
    target[0] = src[6]; target[1] = src[3]; target[2] = src[0];
    target[3] = src[7]; target[4] = src[4]; target[5] = src[1];
    target[6] = src[8]; target[7] = src[5]; target[8] = src[2];
}

void mirror(const char* src, char* target)
{
//state.at(2) << state.at(1) << state.at(0)
//<< state.at(5) << state.at(4) << state.at(3)
//<< state.at(8) << state.at(7) << state.at(6);

    for(int i=0; i<BOARD_SIZE; ++i){
        if(i%3==0)
            target[i] = src[i+2];
        else if(i%3==2)
            target[i] = src[i-2];
        else
            target[i] = src[i];
    }
}

Player* createPlayer(PlayerType type, char mark)
{
    Player* p = nullptr;
    switch(type)
    {
    case PlayerType::Human:
        p = new Player(mark);
        break;
    case PlayerType::Minimax:
        p = new ai::Minimax(mark);
        break;
    case PlayerType::MaybePerfect:
        p = new ai::MaybePerfect(mark);
        break;
    }
    return p;
}



}
