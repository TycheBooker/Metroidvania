#include "Game.h"

Game::Game() :
	window("Metroidvania", sf::Vector2u(800, 600)),
	stateManager(&context)
{
	clock.restart();
	srand(unsigned(time(nullptr)));
	elapsed = sf::Time::Zero;
	context.window = &window;
	context.eventManager = window.getEventManager();
	stateManager.switchTo(StateType::Intro);
}

Game::~Game()
{
}

void Game::update()
{
	window.update();
	stateManager.update(elapsed);
}

void Game::render()
{
	window.beginDraw();
	stateManager.draw();
	window.endDraw();
}

void Game::lateUpdate()
{
	stateManager.processRequests();
	restartClock();
}

Window * Game::getWindow()
{
	return &window;
}

sf::Time Game::getElapsed()
{
	return elapsed;
}

void Game::restartClock()
{
	elapsed += clock.restart();
	float frametime = 1.f / 60.f;
	if (elapsed.asSeconds() >= frametime) {
		elapsed -= sf::seconds(frametime);
	}
}