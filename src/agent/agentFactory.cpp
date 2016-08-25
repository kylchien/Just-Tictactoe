#include "agentFactory.h"
#include "agentFactoryImpl.h"

//std lib
//#include <memory>

//qt lib
//#include <QString>


namespace agent{


std::unique_ptr<AgentFactory::Impl> AgentFactory::impl_
{   new AgentFactory::Impl() };


std::unique_ptr<Agent> AgentFactory::createAgent(QString type, char c)
{
    return impl_->createAgent(type, c);
}

QVariantList AgentFactory::getEnlistedAgents()
{
     return impl_->getEnlistedAgents();
}


	
}//namespace

