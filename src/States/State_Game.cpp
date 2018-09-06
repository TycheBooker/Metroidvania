#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *stateManager) :
	BaseState(stateManager)
{
}

State_Game::~State_Game()
{
}

void State_Game::onCreate()
{
    eventManager->addCallback(StateType::Game, "Key_Escape", &State_Game::openMainMenu, this);
    eventManager->addCallback(StateType::Game, "Key_P", &State_Game::pause, this);
}

void State_Game::onDestroy()
{
    eventManager->removeCallback(StateType::Game, "Key_Escape");
    eventManager->removeCallback(StateType::Game, "Key_P");
}

void State_Game::activate()
{
}

void State_Game::deactivate()
{
}

void State_Game::update(const sf::Time &time)
{}

void State_Game::draw()
{}

void State_Game::openMainMenu(EventDetails *details)
{
    stateManager->switchTo(StateType::MainMenu);
}

void State_Game::pause(EventDetails *details)
{
    stateManager->switchTo(StateType::Paused);
}
