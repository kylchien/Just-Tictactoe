#include "engineImpl.h"
#include "gameUtil.h"
#include "util/runtimeEx.h"
#include "agent/agentFactory.h"
#include "io/simpleWriter.h"

#include <sstream>
#include <vector>

#include <qDebug>

using io::Config;
using io::SimpleWriter;

using namespace agent;

namespace game{

Engine::Impl::Impl():
    curTurn_(MARK_X),
    gameMode_(GameMode::HH),
    playerX_{new Player(MARK_X)},
    playerO_{new Player(MARK_O)},
    config_{new Config(GAME_CONFIG_PATH)}
{
    for(char& c: board_){ c = MARK_E; }
}


Engine::Impl::~Impl()
{}

void Engine::Impl::restart()
{
    for(char& c: board_){ c = MARK_E; }
    curTurn_ = MARK_X;
    gameMode_ = GameMode::HH;

    playerX_->setAgent(AgentFactory::createAgent("Agent", MARK_X));
    playerO_->setAgent(AgentFactory::createAgent("Agent", MARK_O));
}

std::shared_ptr<Player>
Engine::Impl::getPlayer(char mark)
{
    if(mark == MARK_X)
        return playerX_;
    else if(mark == MARK_O)
        return playerO_;
    else{
        std::string msg = "unknown type of player!";
        THROW_RUNTIME_EX(msg);
    }
}

const char* INVALID_GAME_MODE = "invalid game mode!";

bool Engine::Impl::isHumanTurn() const
{
    switch(gameMode_){
        case GameMode::HH:
            return true;
        case GameMode::HM:
            return (curTurn_ == MARK_X)?true:false;
        case GameMode::MH:
            return (curTurn_ == MARK_O)?true:false;
        case GameMode::MM:
            return false;
        default:
            THROW_RUNTIME_EX(INVALID_GAME_MODE);
            break;
    }
    return false;
}

void Engine::Impl::setGameMode(int mode)
{
    gameMode_ = static_cast<GameMode>(mode);
}

void Engine::Impl::createPlayers(int mode, const QString& agentForX, const QString& agentForO)
{
    gameMode_ = static_cast<GameMode>(mode);

    switch(gameMode_){
    case GameMode::HH:
        break;

    case GameMode::HM:
        playerO_->setAgent(AgentFactory::createAgent(agentForO, MARK_O));
        break;

    case GameMode::MH:
        playerX_->setAgent(AgentFactory::createAgent(agentForX, MARK_X));
        break;

    case GameMode::MM:
        playerX_->setAgent(AgentFactory::createAgent(agentForX, MARK_X));
        playerO_->setAgent(AgentFactory::createAgent(agentForO, MARK_O));
        break;

    default:
        THROW_RUNTIME_EX(INVALID_GAME_MODE);
        break;
    }
}


bool Engine::Impl::updateCurPlayerMove(int pos)
{
    if(board_[pos] == MARK_E){
        board_[pos] = curTurn_;
        return true;
    }
    return false;
}

void Engine::Impl::flipTurn()
{
    curTurn_ = (curTurn_ == MARK_X) ? MARK_O : MARK_X;
}

void Engine::Impl::loadBoard(const std::string& board)
{
    for(int i=0; i<BOARD_SIZE; ++i)
        board_[i] = board[i];
    curTurn_ = determineTurn(board_);
}


void record(bool& saving, std::vector<int>& v, int& move)
{ if(saving) v.push_back(move);}


std::string toString(std::vector<int>& v)
{
    std::stringstream ss;
    for(int i:v) ss << i;
    return ss.str();
}


void Engine::Impl::initAgentFromConfig()
{
    QString agentX = config_->get<QString>(PLAYER_X);
    QString agentO = config_->get<QString>(PLAYER_O);
    playerX_->setAgent(AgentFactory::createAgent(agentX, MARK_X));
    playerO_->setAgent(AgentFactory::createAgent(agentO, MARK_O));
}


void Engine::Impl::initWriterFromConfig(WriterPtr& w, bool& savingGame)
{
    savingGame = config_->get<bool>(SAVE_GAME_MODE);

    if(savingGame){
        std::string savePath = config_->get<std::string>(SAVE_DATA_PATH);
        int batchSize = config_->get<int>(SAVE_BATCH_SIZE);
        w = std::make_unique<SimpleWriter>(savePath, batchSize);
    }
}


void Engine::Impl::runOneStep()
{
    config_->initialize();
    initAgentFromConfig();

    if(!isWon(board_) && !isFull(board_)){

        if(curTurn_ == MARK_X){
            int move = playerX_->move(board_);
            board_[move] = MARK_X;
        } else{
            int move = playerO_->move(board_);
            board_[move] = MARK_O;
        }

        flipTurn();
    }else{
        THROW_RUNTIME_EX("game over; unable to advance!");
    }
}


void Engine::Impl::run()
{
    std::vector< std::pair<QString, QString> > vec = {
        {PLAYER_X,"MaybePerfect"},
        {PLAYER_O,"MaybePerfect"},
        {NUM_OF_GAMES, "1"}
    };

    config_->initialize(vec);

    WriterPtr sw = nullptr;
    bool savingGame = false;

    initAgentFromConfig();
    initWriterFromConfig(sw, savingGame);

    int numGames = config_->get<int>(NUM_OF_GAMES);
    for(int i=0;i<numGames;++i){

        //restart
        for(char& c: board_){ c = MARK_E; }
        curTurn_ = MARK_X;

        std::vector<int> vec;

        while(1){
            //player X's turn
			int move = playerX_->move(board_);
			board_[move] = MARK_X;
            record(savingGame, vec, move);

            if(isWon(board_,move)) break;
            else if(isFull(board_)) break;

            //player O's turn
			move = playerO_->move(board_);
			board_[move] = MARK_O;
            record(savingGame, vec, move);

            if(isWon(board_,move)) break;
		}//end while

        playerX_->postProcess();
        playerO_->postProcess();

        if(savingGame){
            sw->writeLine(toString(vec));
        }
	}//end for

}

}//namespace
