#ifndef GAMEDEF
#define GAMEDEF

#include <vector>


namespace game{

static constexpr int BOARD_SIZE = 9;
static constexpr int INVALID = -1;

static constexpr char MARK_X = 'x';
static constexpr char MARK_O = 'o';
static constexpr char MARK_E = '~';

//enum class Outcome{XWIN = 1, OWIN = -1, NIL = 0};
enum class GameMode{HH = 0, HM = 1, MH = 2, MM = 3};

void copyBoard(const char* src, char* tgt);
char determineTurn(const char* curState);

//need to call dealloc in pair
void allocNextStates(char mark, const char* curState, std::vector<char*>& futStates);
void deallocNextStates(std::vector<char*>& futStates);

//determine game outcome
//if winning, provide the positions where marks connect in a row
//Outcome outcome(const char* state, std::vector<int>& winPos);
bool isWon(const char* state, std::vector<int>& winPos);
bool isWon(const char* state, char mark);
bool isFull(const char* state);


bool matchCount(const char* state,
    int i, int j, int k, int countX, int countO, int countE);
int getPos(const char* state, char mark, int i, int j, int k);
bool hasFork(const char* state, char mark);


void rotateCW90(const char* src, char* target);
void mirror(const char* src, char* target);

//Player related:
enum class PlayerType{Human, Minimax, Newell_Simon};
class Player;
Player* createPlayer(PlayerType type, char mark);

}

#endif // GAMEDEF

