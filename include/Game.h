#pragma once
#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void update();
	void render();
	Window * getWindow();
	sf::Time getElapsed();
	void restartClock();
private:
	Window m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};