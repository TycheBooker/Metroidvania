#pragma once
#include <SFML/Graphics.hpp>

class StateManager;
class EventManager;
class Window;

class BaseState
{
	friend class StateManager;

public:
	BaseState(StateManager *stateManager);
	virtual ~BaseState();

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time &timez) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool &transparent);
	bool isTransparent() const;
	void setTranscendent(const bool &transcendent);
	bool isTranscendent() const;
	StateManager *getStateManager();
	sf::View &getView();

protected:
	StateManager *stateManager;
	EventManager *eventManager;
	Window *window;
	sf::View view;

	bool transparent;
	bool transcendent;
};