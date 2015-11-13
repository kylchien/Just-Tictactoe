#ifndef UTILITY_H
#define UTILITY_H

#include <vector>

namespace game{

enum class Outcome{XWIN = 1, OWIN = -1, NIL = 0};
enum class GameMode{HH = 0, HM = 1, MH = 2, MM = 3};

static constexpr int BOARD_SIZE = 9;

char determineTurn(const char* curState);

// have to deallocate after using
void genFutureStates(char mark, const char* curState, std::vector<char*>& futStates);

//determine game outcome
//if winning, provide the positions where marks connect in a row
Outcome outcome(const char* state, std::vector<int>& winPos);

bool isFull(const char* state);

bool isWon(const char* state, char mark);

}

namespace util{

int uniformRand(int min, int max);

void this_thread_sleep(int milliseconds);

}
#endif // UTILITY_H
