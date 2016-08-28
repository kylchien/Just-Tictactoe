#ifndef AGENT_MINIMAX_H
#define AGENT_MINIMAX_H

#include "agent.h"
#include "tieBreaker.h"

namespace agent{


class Minimax : public Agent
{
public:
    Minimax(char mark, bool randomForTie = true);
    virtual ~Minimax();

    virtual int move(const char* state) override;

    static QString type()
    {
        static QString type("Minimax");
        return  type;
    }

    QString getType() override
    { return type(); }

protected:

    static constexpr double INF = 9999;
    static constexpr double WIN = 1;
    static constexpr double LOSE = -1;
    static constexpr double DRAW = 0;
    static constexpr double EPSILON = 0.001;
    static constexpr double DEPTH_ADJ = 0.01;	//enforce no-suicide move
    static constexpr double CENTER_ADJ = 0.005;	//put extra weight on center
    static constexpr int MAX_DEPTH = 9;

    bool random_;
    TieBreaker tieBreaker_;

    bool approxEqual(double f1, double f2, double epsilon);
    double minimax(const char* state, int depth, bool isMax);



};

}
#endif // MINIMAX_H
