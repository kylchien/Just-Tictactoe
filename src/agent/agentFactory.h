#ifndef PLAYERFACTORYNEW_H
#define PLAYERFACTORYNEW_H

#include "agent.h"

//std lib
#include <memory>

//qt lib
#include <QString>
#include <QVariant>

namespace agent{


class AgentFactory{

private:
    AgentFactory() = delete;
    ~AgentFactory() = delete;

    class Impl;
    static std::unique_ptr<Impl> impl_;

public:

    static std::unique_ptr<Agent> createAgent(QString type, char c);

    static QVariantList getEnlistedAgents();
	
};	


	

}
#endif // PLAYERFACTORY_H
