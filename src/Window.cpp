#include "Window.h"

Window::Window()
{
	setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string &t_title, const sf::Vector2u &t_size)
{
	setup(t_title, t_size);
}

Window::~Window()
{
	destroy();
}

void Window::setup(const std::string &t_title, const sf::Vector2u &t_size)
{
	m_windowTitle = t_title;
	m_windowSize = t_size;
	m_isFullscreen = false;
	m_isDone = false;
	create();
}

void Window::create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, style);
	m_window.setFramerateLimit(60);
}

void Window::destroy()
{
	m_window.close();
}

void Window::update()
{
	sf::Event event;
	while(m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			toggleFullscreen();
		}
	}
}

void Window::toggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	destroy();
	create();
}

void Window::beginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	m_window.display();
}

bool Window::isDone()
{
	return m_isDone;
}

bool Window::isFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u Window::getWindowSize()
{
	return m_windowSize;
}

void Window::draw(sf::Drawable & t_drawable)
{
	m_window.draw(t_drawable);
}