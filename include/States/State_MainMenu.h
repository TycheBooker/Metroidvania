#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_MainMenu : public BaseState
{
public:
	State_MainMenu(StateManager * stateManager);
	~State_MainMenu();

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
