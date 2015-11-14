#include "player.h"
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
    if(mark == selfMark_){
        int pos = move(state);
        //delay AI's reponse (600ms) so human can percept its moves
        QTimer::singleShot(600, [this, pos](){emit sendMove(pos);} );
    }
}



}
