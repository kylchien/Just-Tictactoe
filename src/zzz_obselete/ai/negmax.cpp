#include "negmax.h"
#include "../gameDef.h"
#include "../gameUtilFunc.h"
#include "../util/utility.h"

#include <algorithm>
#include <vector>

#include <QDebug>
#include <fstream>

using std::max;
using std::min;
using std::vector;
using std::ofstream;

static bool DEBUG = false;
//ofstream ofs ("C:\\Project\\Just-Tictactoe\\see.txt", std::ofstream::out);

namespace ai{

Negmax::Negmax(char mark, bool randomForTie, bool alphaBeta)
	:Minimax(mark, randomForTie), alphaBeta_(alphaBeta)
{}

Negmax::~Negmax()
{}

int Negmax::move(const char* state)
{
	vector<char*> futStates;
    game::allocNextStates(selfMark_, state, futStates);

    float best = -INFI;
    int bestPos = -1;
    for(unsigned int i =0; i<futStates.size(); ++i){

        char* futState = futStates.at(i);
        int pos = (int)futState[game::BOARD_SIZE];
        float val = alphaBeta_? negmaxAB(futState, MAX_DEPTH-1, pos, -INFI, INFI): negmax(futState, MAX_DEPTH-1, pos);
		
        if(DEBUG) qDebug() << "pos:" << pos << ", val:" << val;

        if(random_ && approxEqual(val, best, EPSILON)){
            tieBreaker_.push_back(pos);
            continue;
        }

        if( val > best){
            best = val;
            bestPos = pos; 
            if(i == 0)							//1st time evaluation always beats the best
                tieBreaker_.push_back(pos);     //we want to put it to tieBreaker
            else
                tieBreaker_.clear();
        }
    }

    if(random_ && !tieBreaker_.empty()){
        int index = util::uniformRand(0,tieBreaker_.size()-1);
        bestPos = tieBreaker_[index];
        tieBreaker_.clear();
    }

    if(DEBUG) qDebug() << "best pos:" << bestPos << "\n";
	
    game::deallocNextStates(futStates);
    return bestPos;
	
}

float Negmax::negmax(const char* state, int depth, int lastMove)
{	
	//negmax always thinks opponent makes perfect move
	//hence, center move is treated as diagonal move - it's no better off
	//if we want to emphasize center, need to introduce centerAdj
	//float centerAdj = 0;
	/*
    if(state[4]== selfMark_)
        centerAdj = CENTER_ADJ;
    else if(state[4] == opponentMark_)
        centerAdj = -CENTER_ADJ;
	*/
    if(game::isWon(state, lastMove)){
		//if(DEBUG) qDebug() << "return WIN for lastMove:" << lastMove;
        return WIN + depth*DEPTH_ADJ;// + centerAdj;
    }
    if(game::isFull(state) || depth == 0){
        //if(DEBUG) qDebug() << "return DRAW";
		return DRAW; //+ centerAdj;
    }

	vector<char*> futStates;
    if(state[lastMove] == opponentMark_)
        game::allocNextStates(selfMark_, state, futStates);
    else
        game::allocNextStates(opponentMark_, state, futStates);

	//opponent always makes the best move to threaten you
    float worst = INFI;
	for(auto futState : futStates){
		int move = (int)futState[game::BOARD_SIZE];
		float val = - negmax(futState, depth-1, move);
		worst = min(worst, val);
	}
    game::deallocNextStates(futStates);
	
	//if(DEBUG) qDebug() << "return worst:" << worst;
	return worst;
}

float Negmax::negmaxAB(const char* state, int depth, int lastMove, float a, float b)
{
	//if(DEBUG){
		//qDebug() << state[0] << state[1] << state[2] << " depth:" << depth << " lastmove:" << lastMove << " a:" << a << " b:" << b;
		//qDebug() << state[3] << state[4] << state[5] << "\n";
		//qDebug() << state[6] << state[7] << state[8] << "\n";
	//}
	
	//negmax always thinks opponent makes perfect move
	//hence, center move is treated as diagonal move - it's no better off
	//if we want to emphasize center, need to introduce centerAdj
	//float centerAdj = 0;
	/*
    if(state[4]== selfMark_)
        centerAdj = CENTER_ADJ;
    else if(state[4] == opponentMark_)
        centerAdj = -CENTER_ADJ;
	*/
    if(game::isWon(state, lastMove)){
		//if(DEBUG) qDebug() << "return WIN " << WIN + depth*DEPTH_ADJ << " for lastMove:" << lastMove;
        return WIN + depth*DEPTH_ADJ;// + centerAdj;
    }
    if(game::isFull(state) || depth == 0){
        //if(DEBUG) qDebug() << "return DRAW";
		return DRAW; //+ centerAdj;
    }

	vector<char*> futStates;
    if(state[lastMove] == opponentMark_)
        game::allocNextStates(selfMark_, state, futStates);
    else
        game::allocNextStates(opponentMark_, state, futStates);

    float worst = INFI;
	for(auto futState : futStates){
		int move = (int)futState[game::BOARD_SIZE];
        float val = - negmaxAB(futState, depth-1, move, -b, -a);
		worst = min(worst, val);
		b = min(b,val);
		if(a>b) {
            //if(DEBUG) qDebug() << "cutoff: " << " a:" << a << " b:" << b;
			break;
		}
	}
    game::deallocNextStates(futStates);
	//if(DEBUG) qDebug() << "return worst:" << worst;
	return worst;
}

}//namespace ai
