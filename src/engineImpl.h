#ifndef ENGINEIMPL_H
#define ENGINEIMPL_H

#include "engine.h"
#include "gameDef.h"
#include "player.h"
#include "io/config.h"
#include "io/simpleWriter.h"

#include <memory>
#include <vector>

#include <QString>

using io::Config;
using io::SimpleWriter;

namespace game{

class Engine::Impl {

private:
    char curTurn_;
    char board_[BOARD_SIZE];
    GameMode gameMode_;

    std::shared_ptr<Player> playerX_;
    std::shared_ptr<Player> playerO_;	
    std::unique_ptr<Config> config_;

    void initAgentFromConfig();

    using WriterPtr = std::unique_ptr<SimpleWriter>;
    void initWriterFromConfig(WriterPtr& w, bool& savingGame);


public:
    Impl();
    ~Impl();

    Impl(const Impl& src) = delete;
    Impl& operator=(const Impl& src) = delete;

	void run();

    void runOneStep();

    void loadBoard(const std::string& board);

    void restart();

    void setGameMode(int mode);

    void createPlayers(int mode, const QString& agentForX, const QString& agentForO);

    void flipTurn();

    bool updateCurPlayerMove(int pos);

    bool isHumanTurn() const;

    std::shared_ptr<Player> getPlayer(char mark);

    inline const char* getBoard() const
    { return board_; }

    inline char getCurrentTurn() const
    { return curTurn_; }

};


}//namesapce

#endif
