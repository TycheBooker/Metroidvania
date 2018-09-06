#pragma once
#include "BaseState.h"
#include "EventManager.h"


class GameState : public BaseState
{
public:
    GameState(StateManager *stateManager);
    ~GameState();

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





