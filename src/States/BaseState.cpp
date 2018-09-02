#include "BaseState.h"

BaseState::BaseState(StateManager * t_stateManager) :
	m_stateManager(t_stateManager),
	m_transparent(false)
{
}

BaseState::~BaseState()
{
}

void BaseState::setTransparent(const bool & t_transparent)
{
	m_transparent = t_transparent;
}

bool BaseState::isTransparent() const
{
	return m_transparent;
}

void BaseState::setTranscendent(const bool & t_transcendent)
{
	m_transcendent = t_transcendent;
}

bool BaseState::isTranscendent() const
{
	return m_transcendent;
}

StateManager * BaseState::getStateManager()
{
	return m_stateManager;
}
