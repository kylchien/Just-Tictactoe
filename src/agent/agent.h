#ifndef AGENT_H
#define AGENT_H

#include "../gameDef.h"

#include <QString>

namespace agent{

class Agent
{

protected:
    char selfMark_;
    char opponentMark_;

public:
    Agent(char mark):selfMark_(mark)
    {
        opponentMark_ = (mark == game::MARK_O)? game::MARK_X : game::MARK_O;
    }

    virtual ~Agent(){}

    Agent(const Agent& src) = delete;
    Agent& operator= (const Agent& src) = delete;

    //omit variable name to "disable" unused variable warning
    virtual int move(const char*)
    {
        return game::INVALID;
    }

    virtual void postProcess(){}

    virtual QString getType()
    {
        return QString("Agent");
    }

    static QString type()
    {
        return QString("Agent");
    }
};



}//namespace agent
#endif
