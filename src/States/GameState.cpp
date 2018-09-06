#include "GameState.h"
#include "StateManager.h"

GameState::GameState(StateManager *stateManager) :
	BaseState(stateManager)
{
}

GameState::~GameState()
{
}

void GameState::onCreate()
{
    eventManager->addCallback(StateType::Game, "Key_Escape", &GameState::openMainMenu, this);
    eventManager->addCallback(StateType::Game, "Key_P", &GameState::pause, this);
}

void GameState::onDestroy()
{
    eventManager->removeCallback(StateType::Game, "Key_Escape");
    eventManager->removeCallback(StateType::Game, "Key_P");
}

void GameState::activate()
{
}

void GameState::deactivate()
{
}

void GameState::update(const sf::Time &time)
{}

void GameState::draw()
{}

void GameState::openMainMenu(EventDetails *details)
{
    stateManager->switchTo(StateType::MainMenu);
}

void GameState::pause(EventDetails *details)
{
    stateManager->switchTo(StateType::Paused);
}
