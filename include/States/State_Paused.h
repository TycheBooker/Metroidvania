#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Paused : public BaseState
{
public:
    State_Paused(StateManager * stateManager);
    ~State_Paused();

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
