//#ifndef	PLAYER_FACTORY_CPP
//#define	PLAYER_FACTORY_CPP

#include "playerFactory.h"
#include "player.h"
#include "ai/ai.h"
#include "util/utility.h"

#include <map>
#include <sstream>
#include <utility>
#include <stdexcept>
	
using std::string;
using std::stringstream;
using std::runtime_error;
using std::map;

using namespace game;
using namespace ai;


namespace game{

std::map<QString, func> PlayerFactory::map_;
bool PlayerFactory::init_ = false;

void PlayerFactory::initialize()
{
	enlist<Player>("Player");
	enlist<MaybePerfect>("MaybePerfect");
	enlist<Minimax>("Minimax");
	enlist<Negmax>("Negmax");
	
	init_ = true;
}

Player* PlayerFactory::create(QString type, char c)
{
	if (!init_) { initialize(); }
	auto func = map_[type];
	return func(c);
}



}//namespace game


/*
static map<QString, PlayerType> str2Type_;
static map<PlayerType, QString> type2Str_;

void initMap()
{
    str2Type_.emplace("Human", PlayerType::Human);
    str2Type_.emplace("MaybePerfect", PlayerType::MaybePerfect);
    str2Type_.emplace("Minimax", PlayerType::Minimax);
	str2Type_.emplace("Negmax", PlayerType::Negmax);
	str2Type_.emplace("NegmaxAB", PlayerType::NegmaxAB);
	
    for(auto pair : str2Type_){
        type2Str_.emplace(pair.second, pair.first);
    }
}

Player* game::createPlayer(PlayerType type, char mark)
{
	Player* p = nullptr;
	switch(type){
		case PlayerType::Human:
			p = new Player(mark);
			break;
		case PlayerType::MaybePerfect:
			p = new MaybePerfect(mark);
			break;
		case PlayerType::Minimax:
			p = new Minimax(mark);
			break;
		case PlayerType::Negmax:
			p = new Negmax(mark);
			break;
		default:
			//shall throw something here
			p = new Player(mark);
			break;
	}
	return p;
}

PlayerType game::toPlayerType(QString str)
{
    if(str2Type_.empty()) initMap();
    if(str2Type_.find(str) == str2Type_.end()){
        string msg = "\"" + str.toStdString() + "\" is not a valid PlayerType";
        throw runtime_error(msg);
    }
    return str2Type_[str];
}


QString game::toString(PlayerType type)
{
    if(str2Type_.empty()) initMap();
    if(type2Str_.find(type) == type2Str_.end()){
        stringstream ss;
        ss << "\"" << static_cast<int>(type) << "\" is not a valid PlayerType";
        throw runtime_error(ss.str());
    }
    return type2Str_[type];
}


Player* game::createPlayer(QString type, char mark)
{
    PlayerType pt = toPlayerType(type);
    return game::createPlayer(pt, mark);
}
*/






//#endif
