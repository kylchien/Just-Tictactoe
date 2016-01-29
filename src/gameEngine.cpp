#include "gameEngine.h"
#include "playerFactory.h"
#include "player.h"
#include ".\\io/save.h"

#include <vector>
#include <sstream>
#include <iostream>

#include <QDebug>
#include <QString>

using namespace std;

namespace game{

GameEngine::GameEngine()
{
	config_ = nullptr;
    initDefault();
}

GameEngine::GameEngine(Config* c):config_(c)
{
	initConfig();
}

GameEngine::~GameEngine()
{
    deletePlayers();
	delete save_;
}


void GameEngine::createHumanPlayers()
{
	playerX_ = PlayerFactory::create("Player", MARK_X);
    playerO_ = PlayerFactory::create("Player", MARK_O);
}

void GameEngine::deletePlayers()
{
    if(playerX_ != nullptr) delete playerX_;
    if(playerO_ != nullptr) delete playerO_;
    playerX_= nullptr;
    playerO_= nullptr;
}

void GameEngine::initDefault()
{
	for(char& c: board_)
        c = MARK_E;
    curTurn_ = MARK_X;

	playerX_ = PlayerFactory::create("MaybePerfect", MARK_X);
    playerO_ = PlayerFactory::create("MaybePerfect", MARK_O);
	maxNumGames_ = 1; 
	isSavingGame_ = false;
	save_ = new Save(); 
}


void GameEngine::initConfig()
{
	for(char& c: board_)
        c = MARK_E;
    curTurn_ = MARK_X;
	
    Config& config = (*config_);
	QString val = config["playerX"];
	if(val != "")
		playerX_ = PlayerFactory::create(val, MARK_X);
	else
		playerX_ = PlayerFactory::create("MaybePerfect", MARK_X);
		
	val = config["playerO"];
	if(val != "")
		playerO_ = PlayerFactory::create(val, MARK_O);
	else
		playerO_ = PlayerFactory::create("MaybePerfect", MARK_O);
	
	val = config["maxNumGames"];
	if(val != "")
		maxNumGames_ = val.toInt();
	else
		maxNumGames_ = 1;
	
	val = config["saveGame"];
	if(val != "")
		isSavingGame_ = (val.toInt()==1)?true:false;
	else
		isSavingGame_ = false;
		
	string savePath = "";
	val = config["saveFilePath"];
	if(val != "")
		savePath = val.toStdString();
	else
        savePath = "." + Save::PATH_DELIMITER;

	int saveBatch;
	val = config["saveBatchSize"];
	if(val != "")
		saveBatch = val.toInt();
	else
        saveBatch = Save::DEFAULT_BATCH_SIZE;
	
	save_ = new Save(savePath, saveBatch);
}

void GameEngine::loadBoard(std::string board)
{
    for(int i=0; i<game::BOARD_SIZE; ++i)
        board_[i] = board[i];
}

void GameEngine::restart()
{
	for(char& c: board_)
        c = MARK_E;
    curTurn_ = MARK_X;
}


void GameEngine::runOneStep(char mark, std::string board)
{
    loadBoard(board);
    int move = (mark == game::MARK_O)?
		playerO_->move(board_):playerX_->move(board_);
    board_[move] = mark;
}


void GameEngine::run()
{
    for(int i=0;i<maxNumGames_;++i){
		restart();
		
        stringstream ss;
        while(1){
            int move = playerX_->move(board_);
            board_[move] = MARK_X;
            if(isSavingGame_) ss << move;
			
            if(isWon(board_,move)){
                if(isSavingGame_) ss << " " << MARK_X;
                break;
            }
            else if(isFull(board_)){
                if(isSavingGame_) ss << " " << MARK_E;
                break;
            }

            move = playerO_->move(board_);
            board_[move] = MARK_O;
            if(isSavingGame_) ss << move;
			
			if(isWon(board_,move)){
                if(isSavingGame_) ss << " " << MARK_O;
				break;
            }
        }
		if(isSavingGame_)
			save_->takeData(ss.str());
    }
}




}//namespace
