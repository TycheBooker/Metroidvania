#pragma once
#include "BaseState.h"
#include "SharedContext.h"
#include "State_Intro.h"

enum class StateType
{
    Intro = 1,
    MainMenu,
    Game,
    Paused,
    GameOver,
    Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState *>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState *(void)>>;

class StateManager
{
  public:
    StateManager(SharedContext *shared);
    ~StateManager();

    void update(const sf::Time &time);
    void draw();

    void processRequests();

    SharedContext *getContext();
    bool hasState(const StateType &type);

    void switchTo(const StateType &type);
    void remove(const StateType &type);

  private:
    void createState(const StateType &type);
    void removeState(const StateType &type);

    template <class T>
    void registerState(const StateType &type);

    SharedContext *shared;
    StateContainer states;
    TypeContainer toRemove;
    StateFactory stateFactory;
};

template <class T>
inline void StateManager::registerState(const StateType &type)
{
    stateFactory[type] = [this]() -> BaseState * {
        return new T(this);
    }
}
