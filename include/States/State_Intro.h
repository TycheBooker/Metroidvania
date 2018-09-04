#pragma once
#include <SFML/Graphics.hpp>
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager * stateManager);
	~State_Intro();

	virtual void onCreate();

	void skip(EventDetails * details);
private:
	sf::Texture introTexture;
	sf::Sprite introSprite;
	sf::Font font;
	sf::Text text;
	float timePassed;
};