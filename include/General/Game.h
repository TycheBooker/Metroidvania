#pragma once
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SharedContext.h"

class Game
{
public:
	Game();
	~Game();

	void update();
	void render();
	void lateUpdate();

	Window * getWindow();
	sf::Time getElapsed();
private:
	SharedContext m_context;
	Window m_window;
	StateManager m_stateManager;
	sf::Clock m_clock;
	sf::Time m_elapsed;
	void restartClock();
};