#ifndef MAYBEPERFECT_H
#define MAYBEPERFECT_H

#include "../player.h"
#include <vector>
#include <functional>

/* This algiorithm is described in
 * Kevin Crowley, Robert S. Siegler (1993).
 * "Flexible Strategy Use in Young Children’s Tic-Tac-Toe".
 * Cognitive Science 17 (4): 531–561
 *
 */

namespace ai{


class MaybePerfect final: public game::Player
{
public:
    explicit MaybePerfect(char mark);
    ~MaybePerfect();

    int move(const char* state);

protected:

    using Function = std::function<int(MaybePerfect*, const char*)>;
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
