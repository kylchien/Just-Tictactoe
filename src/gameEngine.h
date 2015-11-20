#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "gamedef.h"
#include <string>

namespace game{



class Player;

class GameEngine
{
public:
    explicit GameEngine();
    GameEngine(const GameEngine& src) = delete;
    GameEngine& operator=(const GameEngine& src) = delete;
    virtual ~GameEngine();

    void updateBoard(int pos);
    void loadBoard(std::string board);


    //virtual void run();

protected:
    char curTurn_;
    char board_[BOARD_SIZE];

    //unsigned int maxNumGames;

    Player* playerX_;
    Player* playerO_;

    void allocPlayers();
    void allocDefaultPlayers();
    void deallocPlayers();
    void restart();

};










}
#endif // GAMEENGINE_H
