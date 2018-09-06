#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager * stateManager) :
	BaseState(stateManager)
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::onCreate()
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

	eventManager->addCallback(StateType::MainMenu, "Mouse_Left", &MainMenuState::mouseClick, this);
}

void MainMenuState::onDestroy()
{
	eventManager->removeCallback(StateType::MainMenu, "Mouse_Left");
}

void MainMenuState::activate()
{
	if (stateManager->hasState(StateType::Game) && labels[0].getString() == "PLAY") {
		labels[0].setString("RESUME");
		sf::FloatRect labelRect = labels[0].getLocalBounds();
		labels[0].setOrigin(labelRect.left + labelRect.width / 2.f, labelRect.top + labelRect.height / 2.f);
	}
}

void MainMenuState::deactivate()
{
}

void MainMenuState::update(const sf::Time & time)
{
}

void MainMenuState::draw()
{
	window->draw(text);
	for (size_t i = 0; i < 3; i++)
	{
		window->draw(buttons[i]);
		window->draw(labels[i]);
	}
}

void MainMenuState::mouseClick(EventDetails * details)
{
	sf::Vector2f mousePosition = window->getRenderWindow()->mapPixelToCoords(details->mouse);

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
				window->close();
			}
		}
	}
}
