#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "gameEngine.h"
#include <QObject>
#include <QVariant>



namespace game{

class Player;

class TicTacToe : public QObject, public GameEngine
{
    Q_OBJECT

public:
    explicit TicTacToe();
    TicTacToe(const TicTacToe& src) = delete;
    TicTacToe& operator= (const TicTacToe& src) = delete;
    ~TicTacToe();

    Q_INVOKABLE void restart();
    Q_INVOKABLE void initialize();
    Q_INVOKABLE void setGameMode(int mode);
    Q_INVOKABLE void notifyPlayers();
    Q_INVOKABLE bool isHumanTurn() const;
    Q_INVOKABLE QChar getCurrentTurn() const;
    void loadBoard(std::string boardInfo);
    TicTacToe& rotateCW90();
    TicTacToe& mirror();

signals:
    void boardChanged(int pos, char mark);
    void notifyPlayer(char mark, const char* state);
    void gameFinished(QString message);

    //send over the position of connected grids
    void winningPositions(QVariantList list);

    void boardLoaded(QVariantList list);


public slots:
    void updateBoard(int pos);

private:

    GameMode gameMode_;
    QVariantList list_;

    void connectPlayer(Player* p);

};

}//namespace

#endif // TICTACTOE
