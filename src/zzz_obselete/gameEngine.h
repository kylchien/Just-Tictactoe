#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "gamedef.h"
#include "./io/config.h"
#include "./io/save.h"

#include <string>


namespace game{

using std::string;
using io::Config;
using io::Save;

class Player;

class GameEngine
{
public:
    GameEngine();
    explicit GameEngine(Config* c);
    GameEngine(const GameEngine& src) = delete;
    GameEngine& operator=(const GameEngine& src) = delete;
    virtual ~GameEngine();

    void loadBoard(std::string board);
    void run();
    void runOneStep(char mark, std::string board);
	
	
protected:
    void createHumanPlayers();
    void deletePlayers();
    
    void initConfig();
    void initDefault();
    virtual void restart();
	
    char curTurn_;
    char board_[BOARD_SIZE];
    Player* playerX_;
    Player* playerO_;
    int maxNumGames_;
    bool isSavingGame_;
    Config* config_;
    Save* save_;
};



}
#endif // GAMEENGINE_H
