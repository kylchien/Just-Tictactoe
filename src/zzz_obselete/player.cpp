#include "player.h"
#include "gamedef.h"
#include <QTimer>

namespace game{


Player::Player(char mark)
{
    selfMark_ = mark;
	opponentMark_ = (mark == MARK_O)? MARK_X : MARK_O;
}

Player::~Player()
{}

int Player::move(const char* state)
{ return -1;}

void Player::makeMove(char mark, const char* state)
{
    if(mark == selfMark_){
        int pos = move(state);
        //delay AI's reponse (700ms) so human can percept its moves
        QTimer::singleShot(700, [this, pos](){emit sendMove(pos);} );
    }
}



}
