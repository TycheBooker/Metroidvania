#include "BaseState.h"
#include "StateManager.h"

BaseState::BaseState(StateManager *stateManager) :
    stateManager(stateManager),
    transparent(false)
{
    eventManager = stateManager->getContext()->eventManager;
    window = stateManager->getContext()->window;
}

BaseState::~BaseState()
{
}

void BaseState::setTransparent(const bool &transparent)
{
    this->transparent = transparent;
}

bool BaseState::isTransparent() const
{
    return transparent;
}

void BaseState::setTranscendent(const bool &transcendent)
{
    this->transcendent = transcendent;
}

bool BaseState::isTranscendent() const
{
    return transcendent;
}

sf::View& BaseState::getView()
{
	return view;
}

StateManager* BaseState::getStateManager()
{
    return stateManager;
}