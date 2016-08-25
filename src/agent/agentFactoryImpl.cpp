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

    //qDebug() << "AgentFactory creates agent " << type << " for player" << QChar(c);

    auto func = map_[type];
    std::unique_ptr<Agent> p{ func(c)};
    return p;
}

QVariantList AgentFactory::Impl::getEnlistedAgents()
{
    if (!init_) { initialize(); }

    QVariantList list;
    for(auto agentInfo:map_){
        if(agentInfo.first != Agent::type())
            list << agentInfo.first;
    }

    return list;
}



}//namespace agent
