#ifndef Player_H
#define Player_H

#include "agent/agent.h"

#include <memory>

#include <QObject>
#include <QString>

namespace game{


class Player : public QObject
{
    Q_OBJECT

public:

    explicit Player(char mark);
    ~Player();

    Player(const Player& src) = delete;
    Player& operator= (const Player& src) = delete;

    QString getAgentType() const;

    void setAgent(std::unique_ptr<agent::Agent> a);
	
    //inline std::unique_ptr<agent::Agent>& getAgent()
    //{ return agent_; }

	int move(const char* state);
	
signals:
    void sendingMove(int pos);

public slots:
    void makingMove(char mark, const char* state);


private:
    char selfMark_;
    std::unique_ptr<agent::Agent> agent_;
};






}//namespace game
#endif // Player_H
