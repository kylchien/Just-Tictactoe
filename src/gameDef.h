#ifndef GAMEDEF
#define GAMEDEF

#include <vector>


namespace game{

static constexpr int BOARD_SIZE = 9;
static constexpr int INVALID = -1;

static constexpr char MARK_X = 'x';
static constexpr char MARK_O = 'o';
static constexpr char MARK_E = '~';


enum class GameMode{HH = 0, HM = 1, MH = 2, MM = 3};



void copyBoard(const char* src, char* tgt);
char determineTurn(const char* curState);

//need to call dealloc in pair
void allocNextStates(char mark, const char* curState, std::vector<char*>& futStates);
void deallocNextStates(std::vector<char*>& futStates);


//if winning, output the positions where marks are connected in a row in winPos
bool isWon(const char* state);
bool isWon(const char* state, std::vector<int>& winPos);
bool isWon(const char* state, int pos);
bool isWon(const char* state, char mark); //used by minimax
bool isFull(const char* state);


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



}

#endif // GAMEDEF

