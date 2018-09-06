#pragma once
#include "BaseState.h"
#include "EventManager.h"

class PausedState : public BaseState
{
public:
    PausedState(StateManager * stateManager);
    ~PausedState();

    virtual void onCreate();
    virtual void onDestroy();

    virtual void activate();
    virtual void deactivate();

    virtual void update(const sf::Time &time);
    virtual void draw();

    void unpause(EventDetails *details);
private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape overlay;
};
