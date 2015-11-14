#include "player.h"
#include <QDebug>

#include <QTimer>

namespace game{

Player::Player(char mark)
    :selfMark_(mark)
{
    opponentMark_ = (mark == 'o')?'x':'o';
}

Player::~Player()
{}

int Player::move(const char* state)
{ return -1;}

void Player::makeMove(char mark, const char* state)
{
    //qDebug() << "receive mark:" << mark << ", state:" << state;

    if(mark == selfMark_){
        int pos = move(state);
        //emit sendMove(pos);
        QTimer::singleShot(600, [this, pos](){emit sendMove(pos);} );
    }
}



}
