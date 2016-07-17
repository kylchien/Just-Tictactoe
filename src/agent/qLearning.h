#ifndef QLEARNING_H
#define QLEARNING_H

#include "agent.h"
#include "../lookupTable.h"
#include "io/config.h"

#include <memory>
#include <vector>

using game::LookupTable;

namespace agent{

class QLearning : public Agent
{
protected:
    /*
    Q_t1(s_t, a_t) = Q_t(s_t, a_t) +
            alpha_t(s_t, a_t) * {R_t1 + gamma * maxQ_t(s_t1, a_t) - Q_t(s_t, a_t)}
    */
    static constexpr double INF = 9999;
    static constexpr double X_WIN = 1;
    static constexpr double O_WIN = -1;
    static constexpr double DRAW = 0;
    static constexpr double alpha = 0.1;
    static constexpr double gamma = 0.1;
    static constexpr double exploitProb = 0.5;
    static constexpr double EPSILON = 0.0001;

    static bool isInit_;
    static bool isTraining_;

    static std::string dataPath_;
    static std::unique_ptr<io::Config> config_;
    static LookupTable lookupTable_;

    std::vector<int> tieBreaker_;

    double qLearning(const char* sa, int a);

    bool leftBetterThanRight(double lhs, double rhs, char mark);
    int trainMove(const char* state);

	
public:
    QLearning(char mark);
    virtual ~QLearning();

    virtual int move(const char* state) override;

    static void setTraining(bool training)
    { isTraining_ = training; }

    static void print();

    static LookupTable& getLookupTable()
    { return lookupTable_; }

    static QString type()
    {
        static QString type("QLearning");
        return  type;
    }

    QString getType() override
    { return type(); }



	
};

}
#endif // QLEARNING_H
