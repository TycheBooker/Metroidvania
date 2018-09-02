#pragma once
#include "BaseState.h"
#include "SharedContext.h"

enum class StateType
{
	Intro = 1,
	MainMenu,
	Game,
	Paused,
	GameOver,
	Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void )>>;

class StateManager
{
public:
	StateManager(SharedContext * t_shared);
	~StateManager();

	void update(const sf::Time & t_time);
	void draw();
	
	void processRequests();

	SharedContext * getContext();
	bool hasState(const StateType & t_type);

	void switchTo(const StateType & t_type);
	void remove(const StateType & t_type);
private:
	void createState(const StateType & t_type);
	void removeState(const StateType & t_type);

	template<class T>
	void registerState(const StateType & t_type);

	SharedContext * m_shared;
	StateContainer * m_states;
	TypeContainer * m_toRemove;
	StateFactory m_stateFactory;
};

template<class T>
inline void StateManager::registerState(const StateType & t_type)
{
	m_stateFactory[t_type] = [this]() -> BaseState*
	{
		return new T(this);
	}
}
