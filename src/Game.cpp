#include "Game.h"

Game::Game()
{
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