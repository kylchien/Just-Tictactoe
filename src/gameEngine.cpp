#include "gameEngine.h"
#include "player.h"
#include "ai/ai.h"

namespace game{

GameEngine::GameEngine()
{
   restart();
}


GameEngine::~GameEngine()
{
    deallocPlayers();
}


void GameEngine::allocPlayers()
{
    deallocPlayers();
    playerX_ = createPlayer(PlayerType::MaybePerfect, MARK_X);
    playerO_ = createPlayer(PlayerType::Minimax, MARK_O);
}

void GameEngine::allocDefaultPlayers()
{
    deallocPlayers();
    playerX_ = createPlayer(PlayerType::Human, MARK_X);
    playerO_ = createPlayer(PlayerType::Human, MARK_O);
}

void GameEngine::deallocPlayers()
{
    if(playerX_ != nullptr) delete playerX_;
    if(playerO_ != nullptr) delete playerO_;
    playerX_= nullptr;
    playerO_= nullptr;
}


void GameEngine::restart()
{
    for(char& c: board_)
        c = MARK_E;
    curTurn_ = MARK_X;
    allocPlayers();
}

void GameEngine::updateBoard(int pos)
{
    if(board_[pos] == MARK_E)
        board_[pos] = curTurn_;
    else
        return;

    if(isWon(board_,MARK_O) || isWon(board_,MARK_X) || isFull(board_)){
        //stub
    }

    //flip turn
    curTurn_ = (curTurn_ == MARK_X) ? MARK_O : MARK_X;
}




}//namespace
