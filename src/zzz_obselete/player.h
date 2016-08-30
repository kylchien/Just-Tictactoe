#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

namespace game{

class Player : public QObject
{
    Q_OBJECT

public:

	explicit Player(char mark);
	virtual ~Player();

    Player(const Player& src) = delete;
    Player& operator= (const Player& src) = delete;

    virtual int move(const char* state);
	virtual QString getType() const
	{ return QString("Player"); }

signals:
    void sendMove(int pos);

public slots:
    void makeMove(char mark, const char* state);

protected:
    char selfMark_;
    char opponentMark_;
	
};




}
#endif // PLAYER_H