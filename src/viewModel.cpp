#include "viewModel.h"
#include "gameUtil.h"
#include "player.h"

#include <qDebug>

namespace game{

bool ViewModel::isInit = false;

ViewModel::ViewModel():engine_{new Engine()}
{}

ViewModel::~ViewModel()
{}

void ViewModel::createPlayers()
{

    engine_->createPlayers();
    if(!isInit){
        connect(
            this, &ViewModel::notfyingPlayer,
            engine_->getPlayer(MARK_X).get(), &Player::makingMove);
        connect(
            engine_->getPlayer(MARK_X).get(), &Player::sendingMove,
            this, &ViewModel::updateBoard);

        connect(
            this, &ViewModel::notfyingPlayer,
            engine_->getPlayer(MARK_O).get(), &Player::makingMove);
        connect(
            engine_->getPlayer(MARK_O).get(), &Player::sendingMove,
            this, &ViewModel::updateBoard);
            isInit = true;
    }
    notifyPlayers();
}

static int GAMEMODE = -1;
void ViewModel::setGameMode(int mode)
{
    GAMEMODE = mode;
    engine_->setGameMode(mode);
}

bool ViewModel::isHumanTurn() const
{ return engine_->isHumanTurn(); }

QChar ViewModel::getCurrentTurn() const
{ return QChar(engine_->getCurrentTurn()); }


void ViewModel::notifyPlayers()
{
    char curTurn = engine_->getCurrentTurn();
    const char* board = engine_->getBoard();

    if(curTurn == MARK_X)
        emit notfyingPlayer(MARK_X, board);
    else
        emit notfyingPlayer(MARK_O, board);
}

void ViewModel::updateBoard(int pos)
{
    char curTurn = engine_->getCurrentTurn();
    const char* board = engine_->getBoard();

    //update board if it is valid move
    if(engine_->updateCurPlayerMove(pos))
        emit changingBoard(pos, curTurn);
    else
        return; //reject invalid input


    //check if any player wins
    std::vector<int> winPos;
    if(game::isWon(board, winPos)){

        char buf[8] = "  wins!";
        buf[0] = curTurn;
        emit sendingfinishingMsg(QString(buf));

        connectedBlocks_.clear();
        for(auto pos:winPos)   connectedBlocks_ << pos;
        emit markingConnectingBlocks(connectedBlocks_);

        return;
    }

    //check if board is full
    if(game::isFull(board)){
        emit sendingfinishingMsg("draw!");
        return;
    }

    engine_->flipTurn();

    notifyPlayers();
}

void ViewModel::restart()
{
    engine_->restart();
    connectedBlocks_.clear();
}

void ViewModel::loadBoard(std::string boardInfo)
{
    engine_->loadBoard(boardInfo);

    loadedBoard_.clear();
    for(char c: boardInfo)
        loadedBoard_ << QChar(c);

    emit loadingBoard(loadedBoard_);
}


}//namespace game
