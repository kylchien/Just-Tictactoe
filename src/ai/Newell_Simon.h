#ifndef NEWELLSIMON_H
#define NEWELLSIMON_H

#include "../player.h"
#include <vector>
#include <functional>




namespace ai{



class Newell_Simon : public game::Player
{
public:
    explicit Newell_Simon(char mark);
    virtual ~Newell_Simon();

    int move(const char* state);


protected:

    using Function = std::function<int(Newell_Simon*, const char*)>;
    static std::vector<Function> ruleSet_;

    void initialize();
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
