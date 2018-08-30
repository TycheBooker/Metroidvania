#include "EventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::removeCallback(const std::string & t_name)
{
	m_callbacks.erase(t_name);
}

sf::Vector2i EventManager::getMousePos(sf::RenderWindow * t_window)
{
	return (t_window ? sf::Mouse::getPosition(*t_window)
		: sf::Mouse::getPosition());
}
