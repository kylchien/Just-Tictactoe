#include "player.h"

#include <QTimer>
#include <QDebug>

namespace game{

Player::Player(char mark)
    :selfMark_(mark), agent_{nullptr}
{}

Player::~Player()
{}


QString Player::getAgentType() const
{
    return agent_->getType();
}

void Player::setAgent(std::unique_ptr<agent::Agent> a)
{
    agent_ = std::move(a);
}

int Player::move(const char* state)
{
	return (agent_!= nullptr)?(agent_->move(state)):(game::INVALID);
}

void Player::makingMove(char mark, const char* state)
{
    if(mark == selfMark_){
        int move = this->move(state); 
        if( move != game::INVALID){
            //delay AI's reponse (700ms) so human can percept its moves
            QTimer::singleShot(700, [this, move](){emit sendingMove(move);} );
        }
    }
}



}//namespace
