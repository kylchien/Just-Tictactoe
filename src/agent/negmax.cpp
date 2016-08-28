#include "Negmax.h"
#include "gameDef.h"
#include "gameUtil.h"

#include <algorithm>
#include <vector>

#include <QDebug>
#include <fstream>

using std::max;
using std::min;
using std::vector;
using std::ofstream;

static bool DEBUG = false;

namespace agent{

Negmax::Negmax(char mark, bool randomForTie, bool alphaBeta)
    :Minimax(mark, randomForTie), alphaBeta_(alphaBeta)
{
    tieBreaker_.setInitVal(-INF);
}

Negmax::~Negmax()
{}

int Negmax::move(const char* state)
{
    game::NextStates futStates(selfMark_, state);

    double best = -INF;
    int bestPos = -1;

    for(std::size_t i =0; i<futStates.size(); ++i){

        char* futState = futStates.at(i);
        int pos = (int)futState[game::BOARD_SIZE];
        double val = alphaBeta_?
            negmaxAB(futState, MAX_DEPTH-1, pos, -INF, INF):
            negmax(futState, MAX_DEPTH-1, pos);
		
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

double Negmax::negmax(const char* state, int depth, int lastMove)
{	
    double centerAdj = 0;
    if(state[4]== selfMark_)
        centerAdj = CENTER_ADJ;
    else if(state[4] == opponentMark_)
        centerAdj = -CENTER_ADJ;

    if(game::isWon(state, lastMove)){
		//if(DEBUG) qDebug() << "return WIN for lastMove:" << lastMove;
        return WIN + depth*DEPTH_ADJ + centerAdj;
    }
    if(game::isFull(state) || depth == 0){
        //if(DEBUG) qDebug() << "return DRAW";
        return DRAW + centerAdj;
    }

    char mark = (state[lastMove] == opponentMark_)?selfMark_:opponentMark_;
    game::NextStates futStates(mark, state);

	//opponent always makes the best move to threaten you
    double worst = INF;
    for(std::size_t i =0; i<futStates.size(); ++i){
        const char* futState = futStates.at(i);
		int move = (int)futState[game::BOARD_SIZE];
        double val = - negmax(futState, depth-1, move);
		worst = min(worst, val);
	}
	
	//if(DEBUG) qDebug() << "return worst:" << worst;
	return worst;
}

double Negmax::negmaxAB(const char* state, int depth, int lastMove, double a, double b)
{
	//if(DEBUG){
		//qDebug() << state[0] << state[1] << state[2] << " depth:" << depth << " lastmove:" << lastMove << " a:" << a << " b:" << b;
		//qDebug() << state[3] << state[4] << state[5] << "\n";
		//qDebug() << state[6] << state[7] << state[8] << "\n";
	//}
    double centerAdj = 0;
    if(state[4]== selfMark_)
        centerAdj = CENTER_ADJ;
    else if(state[4] == opponentMark_)
        centerAdj = -CENTER_ADJ;

    if(game::isWon(state, lastMove)){
		//if(DEBUG) qDebug() << "return WIN " << WIN + depth*DEPTH_ADJ << " for lastMove:" << lastMove;
        return WIN + depth*DEPTH_ADJ + centerAdj;
    }
    if(game::isFull(state) || depth == 0){
        //if(DEBUG) qDebug() << "return DRAW";
        return DRAW + centerAdj;
    }

    char mark = (state[lastMove] == opponentMark_)?selfMark_:opponentMark_;
    game::NextStates futStates(mark, state);

    double worst = INF;
    for(std::size_t i =0; i<futStates.size(); ++i){
        const char* futState = futStates.at(i);
		int move = (int)futState[game::BOARD_SIZE];
        double val = - negmaxAB(futState, depth-1, move, -b, -a);
		worst = min(worst, val);
		b = min(b,val);
		if(a>b) {
            //if(DEBUG) qDebug() << "cutoff: " << " a:" << a << " b:" << b;
			break;
		}
	}
	//if(DEBUG) qDebug() << "return worst:" << worst;
	return worst;
}

}//namespace ai
