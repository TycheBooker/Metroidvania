#include "Window.h"

Window::Window()
{
    setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string &title, const sf::Vector2u &size)
{
    setup(title, size);
}

Window::~Window()
{
    destroy();
}

void Window::setup(const std::string &title, const sf::Vector2u &size)
{
    windowTitle = title;
    windowSize = size;
    fullscreen = false;
    done = false;
    focused = true;
    eventManager.addCallback(StateType(0), "Fullscreen_toggle", &Window::toggleFullscreen, this);
    eventManager.addCallback(StateType(0), "Window_close", &Window::close, this);
    create();
}

void Window::create()
{
    auto style = (fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    window.create({windowSize.x, windowSize.y, 32}, windowTitle, style);
    window.setFramerateLimit(60);
}

void Window::destroy()
{
    window.close();
}

void Window::update()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::LostFocus) {
            focused = false;
            eventManager.setFocus(false);
        }
        else if (event.type == sf::Event::GainedFocus) {
            focused = true;
            eventManager.setFocus(true);
        }
        eventManager.handleEvent(event);
    }
    eventManager.update();
}

void Window::toggleFullscreen(EventDetails *details)
{
    fullscreen = !fullscreen;
    destroy();
    create();
}

void Window::close(EventDetails *details)
{
    done = true;
}

void Window::beginDraw()
{
    window.clear(sf::Color::Black);
}

void Window::endDraw()
{
    window.display();
}

bool Window::isDone()
{
    return done;
}

bool Window::isFullscreen()
{
    return fullscreen;
}

bool Window::isFocused()
{
    return focused;
}

sf::Vector2u Window::getWindowSize()
{
    return windowSize;
}

sf::RenderWindow* Window::getRenderWindow()
{
    return &window;
}

EventManager* Window::getEventManager()
{
    return &eventManager;
}

void Window::draw(sf::Drawable &drawable)
{
    window.draw(drawable);
}