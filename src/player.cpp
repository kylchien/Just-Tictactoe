#include "player.h"
#include <QDebug>

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
        emit sendMove(pos);
    }
}



}
