#pragma once
#include "BaseState.h"
#include "EventManager.h"


class State_Game : public BaseState
{
public:
    State_Game(StateManager *stateManager);
    ~State_Game();

    virtual void onCreate();
    virtual void onDestroy();

    virtual void activate();
    virtual void deactivate();

    virtual void update(const sf::Time &time) ;
    virtual void draw();

    void openMainMenu(EventDetails *details);
    void pause(EventDetails *details);
private:
};





