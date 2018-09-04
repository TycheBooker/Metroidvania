#include "BaseState.h"

BaseState::BaseState(StateManager * stateManager) :
	stateManager(stateManager),
	transparent(false)
{
}

BaseState::~BaseState()
{
}

void BaseState::setTransparent(const bool & transparent)
{
	this->transparent = transparent;
}

bool BaseState::isTransparent() const
{
	return transparent;
}

void BaseState::setTranscendent(const bool & transcendent)
{
	this->transcendent = transcendent;
}

bool BaseState::isTranscendent() const
{
	return transcendent;
}

StateManager * BaseState::getStateManager()
{
	return stateManager;
}
