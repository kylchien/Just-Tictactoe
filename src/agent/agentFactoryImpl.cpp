#include "agentFactoryImpl.h"
#include "agents.h"
#include "../util/runtimeEx.h"

#include <assert.h>
#include <string>
#include <iostream>

#include <qDebug>


namespace agent{

bool AgentFactory::Impl::init_ = false;
std::map<QString, func> AgentFactory::Impl::map_;


AgentFactory::Impl::Impl()
{}

AgentFactory::Impl::~Impl()
{}

void AgentFactory::Impl::initialize()
{	
    enlist<Agent>(Agent::type());
    enlist<MaybePerfect>(MaybePerfect::type());
    enlist<Minimax>(Minimax::type());
    enlist<Negmax>(Negmax::type());
    enlist<QLearning>(QLearning::type());
    init_ = true;
}



std::unique_ptr<Agent> AgentFactory::Impl::createAgent(QString type, char c)
{
	if (!init_) { initialize(); }

    if(map_.find(type) == map_.end()){
        std::string msg = "Agent Type \'"+ type.toStdString() + "\' is not enlisted";
        THROW_RUNTIME_EX(msg);
    }

    auto func = map_[type];
    std::unique_ptr<Agent> p{ func(c)};
    return p;
}



}//namespace agent
