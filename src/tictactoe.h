#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QObject>
#include <QVariant>
#include "utility.h"
#include <string>


namespace game{

class Player;

class TicTacToe : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToe();
    TicTacToe(const TicTacToe& src) = delete;
    TicTacToe& operator= (const TicTacToe& src) = delete;
    ~TicTacToe();

    Q_INVOKABLE void restart();
    Q_INVOKABLE void initialize();

    //Q_INVOKABLE void playerMoves(int posFromGUI);
    Q_INVOKABLE void setGameMode(int mode);


    Q_INVOKABLE void loadBoard(QString boardInfo);

    Q_INVOKABLE void notifyPlayers();

signals:
    void boardChanged(int pos, char mark);
    void notifyPlayer(char mark, const char* state);
    void gameFinished(QString message);

    //send over the position of connected grids
    void connected(QVariantList list);

    void boardLoaded(QVariantList list);



public slots:
    void updateBoard(int pos);


private:

    GameMode gameMode_;
    char curTurn_;
    char board_[BOARD_SIZE];

    Player* playerX_;
    Player* playerO_;
    void allocateDefaultPlayers();
    void deallocatePlayers();

    QVariantList list_;

};

}//namespace

#endif // TICTACTOE
