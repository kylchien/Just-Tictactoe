#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include <QString>
#include <map>



using std::string;

namespace game{
/*
enum class PlayerType{
    Human=0, MaybePerfect=1, Minimax=2, Negmax=3,
	NegmaxAB=4
};

PlayerType toPlayerType(QString str);
QString toString(PlayerType type);

class Player;
Player* createPlayer(PlayerType type, char mark);
Player* createPlayer(QString type, char mark);
*/

class Player;
typedef Player* (*func)(char mark);

class PlayerFactory{
private:
	PlayerFactory() = default;
	~PlayerFactory() = default;
	
	template <class T>
	static Player* createPlayerFunc(char mark){
		return new T(mark);
	}	
	static void initialize();

	static std::map<QString, func> map_;
	static bool init_;
public:

	template <class T>
	static void enlist(QString playerType){
		map_.emplace(playerType, &createPlayerFunc<T>);
	}
	
	static Player* create(QString type, char c);


	
};	


	

}
#endif // PLAYERFACTORY_H
