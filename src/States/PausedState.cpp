#include "PausedState.h"
#include "StateManager.h"

PausedState::PausedState(StateManager * stateManager) :
    BaseState(stateManager)
{
}

PausedState::~PausedState()
{
}

void PausedState::onCreate()
{
    setTransparent(true);

    font.loadFromFile("data/fonts/arial.ttf");
    text.setFont(font);
    text.setString("PAUSED");
    text.setCharacterSize(14);
    text.setStyle(sf::Text::Bold);

    sf::Vector2u windowSize = window->getWindowSize();

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

    overlay.setSize(sf::Vector2f(windowSize));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    eventManager->addCallback(StateType::Paused, "Key_P", &PausedState::unpause, this);
}

void PausedState::onDestroy()
{
    eventManager->removeCallback(StateType::Paused, "Key_P");
}

void PausedState::activate()
{
}

void PausedState::deactivate()
{
}

void PausedState::update(const sf::Time &time)
{}

void PausedState::draw()
{
    window->draw(overlay);
    window->draw(text);
}

void PausedState::unpause(EventDetails *details)
{
    stateManager->switchTo(StateType::Game);
}