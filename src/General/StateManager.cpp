#include "StateManager.h"

StateManager::StateManager(SharedContext *shared) :
	shared(shared)
{
    registerState<State_Intro>(StateType::Intro);
    //registerState<State_MainMenu>(StateType::MainMenu);
    //registerState<State_Game>(StateType::Game);
    //registerState<State_Paused>(StateType::Paused);
}

StateManager::~StateManager()
{
    for (auto &itr : states)
    {
        itr.second->onDestroy();
        delete itr.second;
    }
}

void StateManager::update(const sf::Time &time)
{
    if (states.empty())
    {
        return;
    }
    if (states.back().second->isTranscendent() && states.size() > 1)
    {
        auto itr = states.end();
        while (itr != states.begin())
        {
            if (itr != states.end())
            {
                if (!itr->second->isTranscendent())
                {
                    break;
                }
            }
            --itr;
        }
        for (; itr != states.end(); ++itr)
        {
            itr->second->update(time);
        }
    }
    else
    {
        states.back().second->update(time);
    }
}

void StateManager::draw()
{
    if (states.empty())
    {
        return;
    }
    if (states.back().second->isTransparent() && states.size() > 1)
    {
        auto itr = states.end();
        while (itr != states.begin())
        {
            if (itr != states.end())
            {
                if (!itr->second->isTransparent())
                {
                    break;
                }
            }
            --itr;
        }
        for (; itr != states.end(); ++itr)
        {
            itr->second->draw();
        }
    }
    else
    {
        states.back().second->draw();
    }
}

void StateManager::processRequests()
{
    while (toRemove.begin() != toRemove.end())
    {
        removeState(*toRemove.begin());
        toRemove.erase(toRemove.begin());
    }
}

SharedContext *StateManager::getContext()
{
    return shared;
}

bool StateManager::hasState(const StateType &type)
{
    for (auto itr = states.begin(); itr != states.end(); ++itr)
    {
        if (itr->first == type)
        {
            auto removed = std::find(toRemove.begin(), toRemove.end(), type);
            if (removed == toRemove.end())
            {
                return true;
            }
        }
    }
    return false;
}

void StateManager::switchTo(const StateType &type)
{
    shared->eventManager->setCurrentState(type);
    for (auto itr = states.begin(); itr != states.end(); ++itr)
    {
        if (itr->first == type)
        {
            states.back().second->deactivate();
            StateType tmp_type = itr->first;
            BaseState *tmp_state = itr->second;
            states.erase(itr);
            states.emplace_back(tmp_type, tmp_state);
            tmp_state->activate();
            return;
        }
    }
    if (!states.empty())
    {
        states.back().second->deactivate();
    }
    createState(type);
    states.back().second->activate();
}

void StateManager::remove(const StateType &type)
{
    toRemove.push_back(type);
}

void StateManager::createState(const StateType &type)
{
    auto newState = stateFactory.find(type);
    if (newState == stateFactory.end())
    {
        return;
    }
    BaseState *state = newState->second();
    states.emplace_back(type, state);
    state->onCreate();
}

void StateManager::removeState(const StateType &type)
{
    for (auto itr = states.begin(); itr != states.end(); ++itr)
    {
        if (itr->first == type)
        {
            itr->second->onDestroy();
            delete itr->second;
            states.erase(itr);
            return;
        }
    }
}
