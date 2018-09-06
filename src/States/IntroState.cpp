#include "IntroState.h"
#include "StateManager.h"

IntroState::IntroState(StateManager *stateManager) :
	BaseState(stateManager)
{
}

IntroState::~IntroState()
{
}

void IntroState::onCreate()
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

    eventManager->addCallback(StateType::Intro, "Intro_Continue", &IntroState::skip, this);
}

void IntroState::onDestroy()
{
    eventManager->removeCallback(StateType::Intro, "Intro_Continue");
}

void IntroState::update(const sf::Time &time)
{
	if (timePassed < 5.f) {
        timePassed += time.asSeconds();
        introSprite.setPosition(introSprite.getPosition().x, introSprite.getPosition().y + (48 * time.asSeconds()));
    }
}

void IntroState::draw()
{
    window->draw(introSprite);
    if (timePassed >= 5.f) {
        window->draw(text);
    }
}

void IntroState::skip(EventDetails *details)
{
    if (timePassed >= 5.f) {
        stateManager->switchTo(StateType::MainMenu);
        stateManager->remove(StateType::Intro);
    }
}

void IntroState::activate()
{
}

void IntroState::deactivate()
{
}