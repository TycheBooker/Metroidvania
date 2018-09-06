#include "State_Paused.h"
#include "StateManager.h"

State_Paused::State_Paused(StateManager * stateManager) :
    BaseState(stateManager)
{
}

State_Paused::~State_Paused()
{
}

void State_Paused::onCreate()
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

    eventManager->addCallback(StateType::Paused, "Key_P", &State_Paused::unpause, this);
}

void State_Paused::onDestroy()
{
    eventManager->removeCallback(StateType::Paused, "Key_P");
}

void State_Paused::activate()
{
}

void State_Paused::deactivate()
{
}

void State_Paused::update(const sf::Time &time)
{}

void State_Paused::draw()
{
    window->draw(overlay);
    window->draw(text);
}

void State_Paused::unpause(EventDetails *details)
{
    stateManager->switchTo(StateType::Game);
}