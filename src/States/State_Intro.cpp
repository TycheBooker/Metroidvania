#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager * t_stateManager) :
	BaseState(t_stateManager)
{
}

State_Intro::~State_Intro()
{
}

void State_Intro::onCreate()
{
	m_timePassed = 0.f;

	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getWindowSize();

	m_introTexture.loadFromFile("data/images/intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.f, m_introTexture.getSize().y / 2.f);
	m_introSprite.setPosition(windowSize.x / 2.f, 0);

	m_font.loadFromFile("data/fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString({ "Press SPACE to continue" });
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBouds();
	m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	m_text.setPosiiton(windowSize.x / 2.f, windowSize.y / 2.f);

	EventManager * eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Intro, "Intro_Continue", &State_Intro::skip, this);
}