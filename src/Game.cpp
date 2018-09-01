#include "Game.h"

Game::Game() : m_window("Metroidvania", sf::Vector2u(800, 600))
{
	m_clock.restart();
	srand(time(nullptr));
	m_elapsed = sf::Time::Zero;
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
	m_window.endDraw();
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