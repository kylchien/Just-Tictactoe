#ifndef NEGMAX_H
#define NEGMAX_H

#include "minimax.h"

namespace ai{

class Negmax : public Minimax
{
public:
    Negmax(char mark, bool randomForTie = true, bool alphaBeta=true);
	virtual ~Negmax();
	virtual int move(const char* state);
	virtual QString getType() const
	{ return QString("Negmax"); }
	
protected:
	float negmax(const char* state, int depth, int lastMove);
	float negmaxAB(const char* state, int depth, int lastMove, float a, float b);
	bool alphaBeta_;
};

}
#endif // NEGMAX_H
