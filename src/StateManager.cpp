#include "..\include\StateManager.h"
#include "..\include\StateManager.h"
#include "..\include\StateManager.h"
#include "..\include\StateManager.h"
#include "..\include\StateManager.h"
#include "..\include\StateManager.h"
#include "..\include\StateManager.h"
#include "StateManager.h"

StateManager::StateManager(SharedContext * t_shared)
{
	register<State_Intro>(StateType::Intro);
	register<State_MainMenu>(StateType::MainMenu);
	register<State_Game>(StateType::Game);
	register<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
	for (auto & itr : m_states)
	{
		itr.second->onDestroy();
		delete itr.second;
	}
}

StateManager::update(const sf::Time & t_time)
{
	if (m_states.empty())
	{
		return;
	}
	if (m_states.back().second->isTranscendent() && m_states - size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->isTranscendent())
				{
					break;
				}
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
		{
			itr->second->update(t_time);
		}
	}
	else
	{
		m_states.back().second->update(t_time);
	}
}

StateManager::draw()
{
	if (m_states.empty())
	{
		return;
	}
	if (m_states.back().second->isTransparend() && m_states.size() > 1)
	{
		auto itr = m_states.end();
		while (itr != m_states.begin())
		{
			if (itr != m_states.end())
			{
				if (!itr->second->isTransparent())
				{
					break;
				}
			}
			--itr;
		}
		for (; itr != m_stated.end(); itr++)
		{
			itr->second.draw();
		}
	}
	else
	{
		m_states.back().second->draw();
	}
}

void StateManager::processRequests()
{
	while (m_toRemove.begin() != m_toRemove.end())
	{
		removeState(*m_toRemove.begin();
		m_toRemove.erase(m_toRemove.begin());
	}
}

SharedContext * StateManager::getContext()
{
	return m_shared;
}

bool StateManager::hasState(const StateType & t_type)
{
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if (itr->first == t_type)
		{
			auto removed = std::find(m_toRemove.begin()), m_toRemove.end(), t_type;
			if (removed == m_toRemove.end())
			{
				return true;
			}
		}
	}
	return false;
}

void StateManager::switchTo(const StateType & t_type)
{
	m_shared->m_eventManager->setCurrentState(t_type);
	for (auto itr = m_states.begin(); itr != m_states.end(); ++itr)
	{
		if (itr->first == t_type)
		{
			m_states.back().second->deactivate();
			StateType tmp_type = itr->first;
			BaseState * tmp_state = itr->second;
			m_states.erase(itr);
			m_states.emplase_back(tmp_type, tmp_state);
			tmp_state->activate();
			return;
		}
	}
	if (!m_states.empty())
	{
		m_states.back().second.->deactivate();
	}
	createState(t_type);
	m_states.back().second->activate();
}

void StateManager::remove(const StateType & t_type)
{
	m_toRemove.push_back(t_type);
}

void StateManager::createState(const StateType & t_type)
{
	auto newState = m_stateFactory.find(t_type);
	if (newState == m_stateFactory.end())
	{
		return;
	}
	BaseState * state = newState->second();
	m_states.emplace_back(t_type, state);
	state->onCreate();
}

void StateManager::removeState(const StateType & t_type)
{
	for (auto itr = m_states.begin(); itr !m_states.end(); ++itr)
	{
		if (itr->first == t_type)
		{
			itr->second->onDestroy();
			delete itr->second;
			m_states.erase(itr);
			reaturn;
		}
	}
}
