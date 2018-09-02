#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <SFML/Graphics.hpp>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1,
	Mouse,
	Joystick
};

struct EventInfo
{
	EventInfo() { m_code = 0; }
	EventInfo(int t_event) { m_code = t_event; }
	union {
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(const std::string & t_bindName)
		: m_name(t_bindName)
	{
		clear();
	}
	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void clear()
	{
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding
{
	Binding(const std::string t_name)
		: m_name(t_name), m_details(t_name), count(0)
	{}

	void bindEvent(EventType t_type, EventInfo t_info = EventInfo())
	{
		m_events.emplace_back(t_type, t_info);
	}

	Events m_events;
	std::string m_name;
	int count;
	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBinding(Binding * t_binding);
	bool removeBinding(std::string t_name);

	void setFocus(const bool & t_focus);

	template<class T>
	bool addCallback(StateType t_state, const std::string & t_name, void(T::*t_func) (EventDetails*), T* t_instance);
	bool removeCallback(StateType t_state, const std::string & t_name);

	void handleEvent(sf::Event & t_event);
	void update();

	sf::Vector2i getMousePos(sf::RenderWindow * t_window = nullptr);
private:
	void loadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	StateType m_currentState;
	bool m_hasFocus;
};

template<class T>
inline bool EventManager::addCallback(StateType t_state, const std::string & t_name, void(T::*t_func) (EventDetails*), T* t_instance)
{
	auto itr = m_callbacks.emplace(
		t_state, CallbackContainer()).first;
	auto callback = std::bind(t_func, t_instance, std::placeholders::_1);
	return itr->second.emplace(t_name, callback).second;
}
