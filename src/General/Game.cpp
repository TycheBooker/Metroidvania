#include "Game.h"

Game::Game() : 
	m_window("Metroidvania", sf::Vector2u(800, 600)),
	m_stateManager(&m_context)
{
	m_clock.restart();
	srand(unsigned int(time(nullptr)));
	m_elapsed = sf::Time::Zero;
	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.getEventManager();
	m_stateManager.switchTo(StateType::Intro);
}

Game::~Game()
{
}

void Game::update()
{
	m_window.update();
}

void Game::render()
{
	m_window.beginDraw();
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::lateUpdate()
{
	m_stateManager.processRequests();
	restartClock();
}

Window * Game::getWindow()
{
	return &m_window;
}

sf::Time Game::getElapsed()
{
	return m_elapsed;
}

void Game::restartClock()
{
	m_elapsed += m_clock.restart();
	float frametime = 1.f / 60.f;
	if (m_elapsed.asSeconds() >= frametime)
	{
		m_elapsed -= sf::seconds(frametime);
	}
}