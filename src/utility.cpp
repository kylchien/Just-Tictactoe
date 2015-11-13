#include "utility.h"
#include <cstring>

#include <random>
#include <chrono>
#include <thread>

#include <QDebug>
#include <sstream>

char game::determineTurn(const char* curState)
{
    int count = 0;
    for(int i=0; i<BOARD_SIZE; ++i){
        if(curState[i] == 'x')
            count++;
        else if(curState[i] =='o')
            count--;
    }
    if(count==0) return 'x';
    return 'o';
}

void game::genFutureStates(char mark, const char* curState, std::vector<char*>& futStates)
{
    for(int i=0; i<BOARD_SIZE; ++i){
        if(curState[i] == ' '){
            char* futState = (char*)malloc(sizeof(char)*(BOARD_SIZE+2));
            std::memcpy(futState, curState, sizeof(char)* BOARD_SIZE);

            futState[i] = mark;
            futState[BOARD_SIZE] = (char)i; //record the index
            futState[BOARD_SIZE+1] = '\0';

            futStates.push_back(futState);
        }
    }
}

game::Outcome game::outcome(const char* state, std::vector<int>& winPos)
{
    Outcome o = Outcome::NIL;

    for(int i=0; i<3; ++i){
        //column check
        if(state[i] != ' ' && state[i] == state[i+3] && state[i] == state[i+6]){
            winPos.push_back(i);
            winPos.push_back(i+3);
            winPos.push_back(i+6);
            o = (state[i] == 'x')?(Outcome::XWIN):(Outcome::OWIN);
        }

        //row check
        if(state[3*i] != ' ' && state[3*i] == state[3*i+1] && state[3*i] == state[3*i+2]){
            winPos.push_back(3*i);
            winPos.push_back(3*i+1);
            winPos.push_back(3*i+2);
            o = (state[3*i] == 'x')?(Outcome::XWIN):(Outcome::OWIN);
        }
    }
    //diagonal check
    if(state[0] != ' ' && state[0] == state[4] && state[0] == state[8]){
        winPos.push_back(0);
        winPos.push_back(4);
        winPos.push_back(8);
        o = (state[0] == 'x')?(Outcome::XWIN):(Outcome::OWIN);
    }
    if(state[2] != ' ' && state[2] == state[4] && state[2] == state[6]){
        winPos.push_back(2);
        winPos.push_back(4);
        winPos.push_back(6);
        o = (state[2] == 'x')?(Outcome::XWIN):(Outcome::OWIN);
    }

    return o;
}

bool game::isWon(const char* state, char mark){
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

bool game::isFull(const char* state)
{
    for(int i=0; i<BOARD_SIZE; ++i)
        if(state[i] == ' ')
            return false;
    return true;
}


//ref http://www.guyrutenberg.com/2014/05/03/c-mt19937-example/
int util::uniformRand(int min, int max)
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 rnd(seed);
    std::uniform_int_distribution<> dist(min, max);
    return dist(rnd);
}

void util::this_thread_sleep(int milliseconds)
{
    std::chrono::milliseconds duration( milliseconds );
    std::this_thread::sleep_for( duration );
}
