#pragma once
#include "BaseState.h"

class State_Intro : public BaseState
{
public:
	State_Intro(StateManager * t_stateManager);
	~State_Intro();

	virtual void onCreate();

	void skip(EventDetails * t_details);
private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Font m_font;
	sf::Text m_text;
	float m_timePassed;
};