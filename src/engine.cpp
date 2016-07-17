#include "engine.h"
#include "engineImpl.h"

namespace game{

Engine::Engine()
	:impl_{  new Engine::Impl()  }
{}

Engine::~Engine()
{}

void Engine::setGameMode(int mode)
{ impl_->setGameMode(mode); }

void Engine::createPlayers()
{ impl_->createPlayers(); }

char Engine::getCurrentTurn() const
{ return impl_->getCurrentTurn(); }

bool Engine::isHumanTurn() const
{ return impl_->isHumanTurn(); }

std::shared_ptr<Player> Engine::getPlayer(char mark)
{ return impl_->getPlayer(mark); }

bool Engine::updateCurPlayerMove(int pos)
{ return impl_->updateCurPlayerMove(pos); }

void Engine::flipTurn()
{ impl_->flipTurn(); }

const char* Engine::getBoard() const
{ return impl_->getBoard(); }

void Engine::restart()
{  return impl_->restart(); }

void Engine::loadBoard(const std::string& board)
{ return impl_->loadBoard(board); }

void Engine::run()
{ return impl_->run(); }



}//namespace game


