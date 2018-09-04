#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window
{
  public:
    Window();
    Window(const std::string &title, const sf::Vector2u &size);
    ~Window();

    void beginDraw(); // Clear the window
    void endDraw();   // Display the changes

    void update();

    bool isDone();
    bool isFullscreen();
    bool isFocused();
    sf::Vector2u getWindowSize();
    EventManager *getEventManager();

    void toggleFullscreen(EventDetails *details);
    void close(EventDetails *details = nullptr);

    void draw(sf::Drawable &drawable);

  private:
    void setup(const std::string &title, const sf::Vector2u &size);
    void destroy();
    void create();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    bool done;
    bool fullscreen;
    EventManager eventManager;
    bool focused;
};