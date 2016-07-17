#ifndef AGENT_MaybePerfect_H
#define AGENT_MaybePerfect_H

#include "agent.h"

#include <vector>
#include <functional>

/*

 This algiorithm is described in
 Kevin Crowley, Robert S. Siegler (1993).
 "Flexible Strategy Use in Young Children’s Tic-Tac-Toe".
 Cognitive Science 17 (4): 531–561

*/


namespace agent{


class MaybePerfect : public Agent
{
public:
    MaybePerfect(char mark);
    virtual ~MaybePerfect();

    MaybePerfect(const MaybePerfect& src) = delete;
    MaybePerfect& operator=(const MaybePerfect&src) = delete;

    int move(const char* state) override;
	
    static QString type()
    {
        static QString type("MaybePerfect");
        return  type;
    }

    QString getType() override
    { return type(); }


protected:
    using Rules = std::function<int(MaybePerfect*, const char*)>;
    static std::vector<Rules> ruleSet_;
    static bool isInit_;
    void initRules();

    int doWin(const char* state);
    int doBlockWin(const char* state);
    int doFork(const char* state);
    int doConnectTwo(const char* state);
    int doBlockFork(const char* state);
    int doCenter(const char* state);
    int doOppositeCorner(const char* state);
    int doEmptyCorner(const char* state);
    int doEmptySide(const char* state);

};


}

#endif // NEWELLSIMON_H
