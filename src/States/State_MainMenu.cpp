#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager * stateManager) :
	BaseState(stateManager)
{
}

State_MainMenu::~State_MainMenu()
{
}

void State_MainMenu::onCreate()
{
	font.loadFromFile("data/fonts/arial.ttf");
	text.setFont(font);
	text.setString("MAIN MENU:");
	text.setCharacterSize(18);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	text.setPosition(400, 100);

	buttonSize = sf::Vector2f(300.f, 32.f);
	buttonPos = sf::Vector2f(400, 200);
	buttonPadding = 4;

	std::string strings[3];
	strings[0] = "PLAY";
	strings[1] = "CREDITS";
	strings[2] = "EXIT";

	for (size_t i = 0; i < 3; i++)
	{
		sf::Vector2f buttonPosition(buttonPos.x, buttonPos.y + (i * (buttonSize.y + buttonPadding)));
		buttons[i].setSize(buttonSize);
		buttons[i].setFillColor(sf::Color::Red);

		buttons[i].setOrigin(buttonSize.x / 2.f, buttonSize.y / 2.f);
		buttons[i].setPosition(buttonPosition);

		labels[i].setFont(font);
		labels[i].setString(strings[i]);
		labels[i].setCharacterSize(12);

		sf::FloatRect labelRect = labels[i].getLocalBounds();
		labels[i].setOrigin(labelRect.left + labelRect.width / 2.f, labelRect.top + labelRect.height / 2.f);

		labels[i].setPosition(buttonPosition);
	}

	EventManager * eventManager = stateManager->getContext()->eventManager;
	eventManager->addCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::mouseClick, this);
}

void State_MainMenu::onDestroy()
{
	EventManager * eventManager = stateManager->getContext()->eventManager;
	eventManager->removeCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::activate()
{
	if (stateManager->hasState(StateType::Game) && labels[0].getString() == "PLAY") {
		labels[0].setString("RESUME");
		sf::FloatRect labelRect = labels[0].getLocalBounds();
		labels[0].setOrigin(labelRect.left + labelRect.width / 2.f, labelRect.top + labelRect.height / 2.f);
	}
}

void State_MainMenu::deactivate()
{
}

void State_MainMenu::update(const sf::Time & time)
{
}

void State_MainMenu::draw()
{
	sf::RenderWindow *window = stateManager->getContext()->window->getRenderWindow();
	window->draw(text);
	for (size_t i = 0; i < 3; i++)
	{
		window->draw(buttons[i]);
		window->draw(labels[i]);
	}
}

void State_MainMenu::mouseClick(EventDetails * details)
{
	sf::RenderWindow *window = stateManager->getContext()->window->getRenderWindow();
	sf::Vector2f mousePosition = window->mapPixelToCoords(details->mouse);

	for (size_t i = 0; i < 3; i++)
	{
		if (buttons[i].getGlobalBounds().contains(mousePosition)) {
			if (i == 0) {
				stateManager->switchTo(StateType::Game);
			}
			else if (i == 1) {
				stateManager->switchTo(StateType::Credits);
			}
			else if (i == 2) {
				stateManager->getContext()->window->close();
			}
		}
	}
}
