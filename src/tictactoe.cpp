#include "tictactoe.h"
#include "player.h"
#include "ai/ai.h"
#include <QtDebug>



namespace game{

TicTacToe::TicTacToe()
{
    restart();
}

TicTacToe::~TicTacToe()
{
    GameEngine::deallocPlayers();
}

void TicTacToe::setGameMode(int mode)
{
    gameMode_ = static_cast<GameMode>(mode);
}


void TicTacToe::restart()
{
    for(char& c: board_)
        c = MARK_E;

    GameEngine::allocDefaultPlayers();
    curTurn_ = MARK_X;
    gameMode_ = GameMode::HH;
    list_.clear();
}

void TicTacToe::connectPlayer(Player* p)
{
    connect(this, &TicTacToe::notifyPlayer,
            p, &Player::makeMove);
    connect(p, &Player::sendMove,
            this, &TicTacToe::updateBoard);
}

void TicTacToe::initialize()
{
    switch(gameMode_){
    case GameMode::HH:
        GameEngine::allocDefaultPlayers();
        break;

    case GameMode::HM:
        playerX_ = createPlayer(PlayerType::Human, MARK_X);
        playerO_ = createPlayer(PlayerType::MaybePerfect, MARK_O);
        connectPlayer(playerO_);
        break;

    case GameMode::MH:
        playerO_ = createPlayer(PlayerType::Human, MARK_O);
        playerX_ = createPlayer(PlayerType::MaybePerfect, MARK_X);
        connectPlayer(playerX_);
        break;

    case GameMode::MM:
        playerX_ = createPlayer(PlayerType::MaybePerfect, MARK_X);
        playerO_ = createPlayer(PlayerType::Minimax, MARK_O);
        connectPlayer(playerX_);
        connectPlayer(playerO_);
        break;

    default:
        qFatal("unknown game mode!!!");
        break;
    }

    curTurn_ = determineTurn(board_);
    notifyPlayers();
}

void TicTacToe::notifyPlayers()
{
    if(curTurn_ == MARK_X)
        emit notifyPlayer(MARK_X, board_);
    else
        emit notifyPlayer(MARK_O, board_);
}


void TicTacToe::loadBoard(std::string boardInfo)
{
   for(int i=0; i<BOARD_SIZE; ++i)
       board_[i] = boardInfo[i];

   list_.clear();
   for(char c: board_)
       list_ << QChar(c);

   emit boardLoaded(list_);
}


void TicTacToe::updateBoard(int pos)
{
    if(board_[pos] == MARK_E){
        board_[pos] = curTurn_;
        emit boardChanged(pos, curTurn_);
    }
    //reject invalid input
    else
        return;

    //check any player wins
    std::vector<int> winPos;
    if(isWon(board_, winPos)){
        char buf[8] = "  wins!";
        buf[0] = curTurn_;
        emit gameFinished(QString(buf));

        //send out the indices of connected grids to GUI
        list_.clear();
        for(auto pos:winPos)
            list_ << pos;
        emit winningPositions(list_);

        return;
    }

    //check board is full
    if(isFull(board_)){
        emit gameFinished("draw!");
        return;
    }

    //flip turn
    curTurn_ = (curTurn_ == MARK_X) ? MARK_O : MARK_X;

    notifyPlayers();

}


QChar TicTacToe::getCurrentTurn() const
{
    return QChar(curTurn_);
}

bool TicTacToe::isHumanTurn() const
{
    switch(gameMode_){
    case GameMode::HH:
        return true;
    case GameMode::HM:
        if(curTurn_ == MARK_X)
            return true;
        else
            return false;
    case GameMode::MH:
        if(curTurn_ == MARK_O)
            return true;
        else
            return false;
    case GameMode::MM:
        return false;
    }
    return false;
}

TicTacToe& TicTacToe::rotateCW90()
{
    char newBoard[BOARD_SIZE];
    game::rotateCW90(board_, newBoard);
    copyBoard(newBoard, board_);
    list_.clear();
    for(char c: board_)
        list_ << QChar(c);

    emit boardLoaded(list_);
    return *this;
}

TicTacToe& TicTacToe::mirror()
{
    char newBoard[BOARD_SIZE];
    game::mirror(board_, newBoard);
    copyBoard(newBoard, board_);
    list_.clear();
    for(char c: board_)
        list_ << QChar(c);

    emit boardLoaded(list_);
    return *this;
}


}
