#include "tictactoe.h"
#include "player.h"
#include "ai/ai.h"
#include <QtDebug>
#include <sstream>




namespace game{

TicTacToe::TicTacToe()
{
    restart();
}

TicTacToe::~TicTacToe()
{
    deallocatePlayers();
}

void TicTacToe::setGameMode(int mode)
{
    gameMode_ = static_cast<GameMode>(mode);
    qDebug() << "set game mode to " << static_cast<int>(gameMode_);
}



void TicTacToe::deallocatePlayers()
{
    if(playerX_ != nullptr) delete playerX_;
    if(playerO_ != nullptr) delete playerO_;
    playerX_= nullptr;
    playerO_= nullptr;
}

//handle the case that user directly closes optionWindow
//without choosing game mode
void TicTacToe::allocateDefaultPlayers()
{
    deallocatePlayers();
    playerX_ = new Player('x');
    playerO_ = new Player('o');

}

void TicTacToe::restart()
{
    for(int i=0; i<BOARD_SIZE; ++i)
        board_[i] = ' ';

    curTurn_ = 'x';
    gameMode_ = GameMode::HH;
    allocateDefaultPlayers();

    list_.clear();
}

void TicTacToe::initialize()
{
    //handle the case that user directly closes optionWindow
    //without choosing game mode
    deallocatePlayers();

    switch(gameMode_){
    case GameMode::HH:
        allocateDefaultPlayers();
        break;

    case GameMode::HM:
        playerX_ = new Player('x');
        playerO_ = new ai::Minimax('o');
        connect(this,     &TicTacToe::notifyPlayer,
                playerO_, &Player::makeMove);
        connect(playerO_, &Player::sendMove,
                this,     &TicTacToe::updateBoard);
        break;

    case GameMode::MH:
        playerO_ = new Player('o');
        playerX_ = new ai::Minimax('x');
        connect(this,     &TicTacToe::notifyPlayer,
                playerX_, &Player::makeMove);
        connect(playerX_, &Player::sendMove,
                this,     &TicTacToe::updateBoard);
        break;

    case GameMode::MM:
        playerX_ = new ai::Minimax('x');
        connect(this,     &TicTacToe::notifyPlayer,
                playerX_, &Player::makeMove);
        connect(playerX_, &Player::sendMove,
                this,     &TicTacToe::updateBoard);
        playerO_ = new ai::Minimax('o');
        connect(this,     &TicTacToe::notifyPlayer,
                playerO_, &Player::makeMove);
        connect(playerO_, &Player::sendMove,
                this,     &TicTacToe::updateBoard);
        break;

    default:
        qFatal("unknown game mode!!!");
        break;
    }

    //due to board-loading feature, we cannot simply set turn here
    //need to evaluate entire board and decide whose turn
    curTurn_ = determineTurn(board_);
    notifyPlayers();

}

void TicTacToe::notifyPlayers()
{
    if(curTurn_ == 'x')
        emit notifyPlayer('x', board_);
    else
        emit notifyPlayer('o', board_);
}


void TicTacToe::loadBoard(QString boardInfo)
{
   list_.clear();
   int count = 0;
   for(int i=0; i<BOARD_SIZE; ++i){
       char c = boardInfo.at(i).toLatin1();
       board_[i] = c;
       if(c == 'x')     count++;
       else if(c =='o') count--;
   }

   if(count>0) curTurn_ = 'o';
   else        curTurn_ = 'x';

   for(int i=0; i<BOARD_SIZE; ++i){
       list_ << QChar(board_[i]);
   }

   emit boardLoaded(list_);
}




//void TicTacToe::updateBoard(int pos, char mark)
void TicTacToe::updateBoard(int pos)
{
    if(board_[pos] == ' '){
        board_[pos] = curTurn_;
        emit boardChanged(pos, curTurn_);
    }
    //reject invalid input
    else
        return;

    //check any player wins
    std::vector<int> winPos;
    if(outcome(board_, winPos) != Outcome::NIL){
        std::ostringstream oss;
        oss << curTurn_ << " wins!";
        emit gameFinished(QString(oss.str().c_str()));

        //send out the indices of connected grids to GUI
        list_.clear();
        for(auto pos:winPos)
            list_ << pos;
        emit connected(list_);

        return;
    }

    //check board is full
    if(isFull(board_)){
        emit gameFinished("draw!");
        return;
    }

    //flip turn
    curTurn_ = (curTurn_ == 'x')?'o':'x';

    notifyPlayers();

}




}
