#include "player.h"
#include "gameDef.h"

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
            //delay AI's reponse (in msec) so human can perceive its moves
            QTimer::singleShot(
                AI_RESPONSE_DELAY,
                [this, move](){emit sendingMove(move);}
            );
        }
    }
}

void Player::postProcess()
{
    agent_->postProcess();
}



}//namespace
