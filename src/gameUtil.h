#ifndef GAMEUTILFUNC_H
#define GAMEUTILFUNC_H

#include "gameDef.h"
#include "io/simpleWriter.h"

#include <vector>
#include <memory>

namespace game{

class NextStates
{
public:
    NextStates(char mark, const char* curState);
    ~NextStates();

    NextStates(const NextStates& src);
    NextStates& operator=(NextStates src);

    NextStates(NextStates&& src);
    NextStates& operator=(NextStates&& src);

    inline std::size_t size() { return size_; }
    char* at(std::size_t idx);

    friend void swap(NextStates& lhs, NextStates& rhs);

private:
    std::size_t size_;
    char* states_;
};

void copyBoard(const char* src, char* tgt);
char determineTurn(const char* curState);


//if winning, output the positions where marks are connected in a row in winPos
bool isWon(const char* state);
bool isWon(const char* state, std::vector<int>& winPos);
bool isWon(const char* state, int pos);
bool isWon(const char* state, char mark); //used by minimax
bool isFull(const char* state);

bool isEqual(const char* lhs, const char* rhs);


//check in the positions i,j,k, the number of O, the number of X, the number of empty, 
//do match the given countX, countO, countE, respectively
//if so return true, otherwise return false
bool matchCount(const char* state,
    int i, int j, int k, int countX, int countO, int countE);
	
//given a mark (X, O or empty), and a particular row (i,j,k)
//return its position; the check priority is i, j, k
//this function is utilized with matchCount:
//first using matchCount to check, say, two x's and one empty spot in certain row (i,j,k)
//then, we need to get the exact location of that empty spot
int getPos(const char* state, char mark, int i, int j, int k);

//check whether the board has a FORK with given mark, that is:
//2 x row which contains two same marks with one empty slot 
bool hasFork(const char* state, char mark);


void rotateCW90(const char* src, char* target);
void mirror(const char* src, char* target);

std::shared_ptr<io::SimpleWriter>
makeWriterFromGameConfig();

}

#endif //GAMEUTILFUNC_H

/*
/// <A short one line description>
///
/// <Longer description>
/// <May span multiple lines or paragraphs as needed>
///
/// @param  Description of method's or function's input parameter
/// @param  ...
/// @return Description of the return value
*/
