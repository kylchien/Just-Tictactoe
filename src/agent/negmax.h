#ifndef AGENT_Negmax_H
#define AGENT_Negmax_H

#include "minimax.h"

namespace agent{

class Negmax : public Minimax
{
public:
    Negmax(char mark, bool randomForTie = true, bool alphaBeta=true);
    virtual ~Negmax();
	virtual int move(const char* state);

    static QString type()
    {
        static QString type("Negmax");
        return  type;
    }

    QString getType() override
    { return type(); }
	
protected:
    double negmax(const char* state, int depth, int lastMove);
    double negmaxAB(const char* state, int depth, int lastMove, double a, double b);
	bool alphaBeta_;
};

}
#endif // Negmax_H
