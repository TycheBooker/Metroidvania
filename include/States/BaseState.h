#pragma once
#include <SFML/System.hpp>

class StateManager;

class BaseState
{
	friend class StateManager;
public:
	BaseState(StateManager * t_stateManager);
	virtual ~BaseState();

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time & t_timez) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool & t_transparent);
	bool isTransparent() const;
	void setTranscendent(const bool & t_transcendent);
	bool isTranscendent() const;
	StateManager* getStateManager();
protected:
	StateManager * m_stateManager;
	bool m_transparent;
	bool m_transcendent;
};