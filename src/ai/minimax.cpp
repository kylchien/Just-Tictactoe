#include "minimax.h"
#include "../utility.h"
#include "../tictactoe.h"
#include <algorithm>
#include <QDebug>
#include <fstream>


using std::vector;
using std::max;
using std::min;

static bool DEBUG = true;

bool approxEqual(float f1, float f2, float epsilon)
{
    float diff = ((f1 - f2)>0)?(f1 - f2):((f1 - f2)*-1);
    return diff < epsilon;
}

//std::ofstream stream;

namespace ai{

Minimax::Minimax(char mark, bool randomForTie)
    :Player(mark), random_(randomForTie)
{
    //std::string s="C:\\Users\\m0neyp1g\\Desktop\\see.txt";
    //stream.open(s);
}


Minimax::~Minimax()
{
    //stream.close();
}



int Minimax::move(const char* state)
{

    vector<char*> futStates;
    game::allocNextStates(selfMark_, state, futStates);

    float best = -INFI;
    int bestPos = -1;
    for(unsigned int i =0; i<futStates.size(); ++i){

        char* futState = futStates.at(i);
        int pos = (int)futState[game::BOARD_SIZE];
        float val = minimax(futState, MAX_DEPTH-1, false);

        if(DEBUG)
            qDebug() << "pos:" << pos << ", val:" << val;

        if(random_ && approxEqual(val, best, EPSILON)){
            tieBreaker_.push_back(pos);
            continue;
        }

        if( val > best){
            best = val;
            bestPos = pos;

            //first evaluation always beats the best(which is -ininity)
            //we want to put it to tieBreaker as well
            if(i == 0)
                tieBreaker_.push_back(pos);
            else
                tieBreaker_.clear();
        }
    }

    if(random_ && !tieBreaker_.empty()){
        if(DEBUG)
            for(int index : tieBreaker_)
                qDebug() << "tieBreaker:" << index;

        int index = util::uniformRand(0,tieBreaker_.size()-1);
        bestPos = tieBreaker_[index];
        tieBreaker_.clear();
    }

    if(DEBUG)
        qDebug() << "best pos:" << bestPos << "\n";

    game::deallocNextStates(futStates);
    return bestPos;
}


float Minimax::minimax(const char* state, int depth, bool isMax)
{
    float centerAdj = 0;
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
        //int sign = (isMax)?1:-1;
        //return DRAW + sign*(depth*DEPTH_ADJ);
        return DRAW + centerAdj;
    }


    vector<char*> futStates;
    if(isMax)
        game::allocNextStates(selfMark_, state, futStates);
    else
        game::allocNextStates(opponentMark_, state, futStates);

    float best;
    if(isMax){
        best = -INFI;
        for(auto futState : futStates)
            best = max(best, minimax(futState, depth-1, false));
    }
    else{
        best = INFI;
        for(auto futState : futStates)
            best = min(best, minimax(futState, depth-1, true));
    }

    game::deallocNextStates(futStates);
    return best;
}


}


/* test case:
 *
 *  //depth testing, ai:o
    //gameInstance.loadBoard("~x~~~xoox");
 */
