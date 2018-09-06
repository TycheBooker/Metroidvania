#pragma once
#include "BaseState.h"
#include "EventManager.h"

class MainMenuState : public BaseState
{
public:
	MainMenuState(StateManager * stateManager);
	~MainMenuState();

	virtual void onCreate();
	virtual void onDestroy();

	virtual void activate();
	virtual void deactivate();

	virtual void update(const sf::Time &time);
	virtual void draw();

	void mouseClick(EventDetails * details);
private:
	sf::Font font;
	sf::Text text;

	sf::Vector2f buttonSize;
	sf::Vector2f buttonPos;
	unsigned buttonPadding;

	sf::RectangleShape buttons[3];
	sf::Text labels[3];
};
