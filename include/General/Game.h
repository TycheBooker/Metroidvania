#pragma once
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "ResourceManager.h"

class Game
{
  public:
    Game();
    ~Game();

    void update();
    void render();
    void lateUpdate();

    Window *getWindow();
    sf::Time getElapsed();

  private:
    SharedContext context;
    Window window;
    StateManager stateManager;
    sf::Clock clock;
    sf::Time elapsed;
    void restartClock();
};