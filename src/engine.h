#ifndef ENGINE_H
#define ENGINE_H

#include <memory>


namespace game{

class Player;

class Engine final{

public:
    Engine();
    ~Engine();

    Engine(const Engine& src) = delete;
    Engine& operator=(const Engine& src) = delete;


	void run();
/*
    void runOnePlayerTurn(char mark, std::string board);
*/
    void loadBoard(const std::string& board);
    void restart();
    void setGameMode(int mode);
    void createPlayers();

    bool isHumanTurn() const;

    std::shared_ptr<Player> getPlayer(char mark);

    bool updateCurPlayerMove(int pos);
    void flipTurn();
    const char* getBoard() const;
    char getCurrentTurn() const;


private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


}//namesapce

#endif
