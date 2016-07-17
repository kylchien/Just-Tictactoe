#ifndef PLAYERFACTORYNEW_H
#define PLAYERFACTORYNEW_H

#include "agent.h"

//std lib
#include <memory>

//qt lib
#include <QString>


namespace agent{


class AgentFactory{

private:
    AgentFactory() = delete;
    ~AgentFactory() = delete;

    class Impl;
    static std::unique_ptr<Impl> impl_;

public:

    static std::unique_ptr<Agent> createAgent(QString type, char c);


	
};	


	

}
#endif // PLAYERFACTORY_H
