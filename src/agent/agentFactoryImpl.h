#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "agentFactory.h"

//std lib
#include <map>
#include <memory>

//qt lib
#include <QString>


namespace agent{

class Agent;
typedef Agent* (*func)(char mark);

class AgentFactory::Impl{

private:
    static bool init_;
    static std::map<QString, func> map_;

    static void initialize();

    template <class T>
    static Agent* createAgentFunc(char mark){
        return new T(mark);
    }

    template <class T>
    static void enlist(QString agentType){
        map_.emplace(agentType, &createAgentFunc<T>);
    }

public:
    Impl();
    ~Impl();

    Impl(const Impl& src) = delete;
    Impl& operator= (const Impl& src) = delete;

    std::unique_ptr<Agent> createAgent(QString type, char c);

};	


	

}
#endif // PLAYERFACTORY_H
