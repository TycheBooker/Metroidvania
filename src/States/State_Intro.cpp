#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager *stateManager) :
	BaseState(stateManager)
{
}

State_Intro::~State_Intro()
{
}

void State_Intro::onCreate()
{
    timePassed = 0.f;

    sf::Vector2u windowSize = stateManager->getContext()->window->getWindowSize();

    introTexture.loadFromFile("data/images/intro.png");
    introSprite.setTexture(introTexture);
    introSprite.setOrigin(introTexture.getSize().x / 2.f, introTexture.getSize().y / 2.f);
    introSprite.setPosition(windowSize.x / 2.f, 0);

    font.loadFromFile("data/fonts/arial.ttf");
    text.setFont(font);
    text.setString({"Press SPACE to continue"});
    text.setCharacterSize(15);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

    eventManager->addCallback(StateType::Intro, "Intro_Continue", &State_Intro::skip, this);
}

void State_Intro::onDestroy()
{
    eventManager->removeCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::update(const sf::Time &time)
{
	if (timePassed < 5.f) {
        timePassed += time.asSeconds();
        introSprite.setPosition(introSprite.getPosition().x, introSprite.getPosition().y + (48 * time.asSeconds()));
    }
}

void State_Intro::draw()
{
    window->draw(introSprite);
    if (timePassed >= 5.f) {
        window->draw(text);
    }
}

void State_Intro::skip(EventDetails *details)
{
    if (timePassed >= 5.f) {
        stateManager->switchTo(StateType::MainMenu);
        stateManager->remove(StateType::Intro);
    }
}

void State_Intro::activate()
{
}

void State_Intro::deactivate()
{
}