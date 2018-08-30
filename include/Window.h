#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	Window(const std::string &t_title, const sf::Vector2u &t_size);
	~Window();

	void beginDraw(); // Clear the window
	void endDraw();   // Display the changes

	void update();

	bool isDone();
	bool isFullscreen();
	sf::Vector2u getWindowSize();

	void toggleFullscreen();

	void draw(sf::Drawable &t_drawable);

private:
	void setup(const std::string &t_title, const sf::Vector2u &t_size);
	void destroy();
	void create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};