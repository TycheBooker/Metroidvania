#pragma once
#include <vector>
#include <map>
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
    EventInfo() { code = 0; }
    EventInfo(int event) { code = event; }
    union {
        int code;
    };
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
    EventDetails(const std::string &bindName)
        : name(bindName)
    {
        clear();
    }
    std::string name;
    sf::Vector2i size;
    sf::Uint32 textEntered;
    sf::Vector2i mouse;
    int mouseWheelDelta;
    int keyCode;

    void clear()
    {
        size = sf::Vector2i(0, 0);
        textEntered = 0;
        mouse = sf::Vector2i(0, 0);
        mouseWheelDelta = 0;
        keyCode = -1;
    }
};

struct Binding
{
    Binding(const std::string name)
        : name(name), details(name), count(0)
    {
    }

    void bindEvent(EventType type, EventInfo info = EventInfo())
    {
        events.emplace_back(type, info);
    }

    Events events;
    std::string name;
    int count;
    EventDetails details;
};

using Bindings = std::unordered_map<std::string, Binding *>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails *)>>;
enum class StateType;
using Callbacks = std::map<StateType, CallbackContainer>;

class EventManager
{
  public:
    EventManager();
    ~EventManager();

    bool addBinding(Binding *binding);
    bool removeBinding(std::string name);

    void setCurrentState(StateType state);
    void setFocus(const bool &focus);

    template <class T>
    bool addCallback(StateType state, const std::string &name, void (T::*func)(EventDetails *), T *instance);
    bool removeCallback(StateType state, const std::string &name);

    void handleEvent(sf::Event &event);
    void update();

    sf::Vector2i getMousePos(sf::RenderWindow *window = nullptr);

  private:
    void loadBindings();

    Bindings bindings;
    Callbacks callbacks;
    StateType currentState;
    bool hasFocus;
};

template <class T>
inline bool EventManager::addCallback(StateType state, const std::string &name, void (T::*func)(EventDetails *), T *instance)
{
    auto itr = callbacks.emplace(state, CallbackContainer()).first;
    auto callback = std::bind(func, instance, std::placeholders::_1);
    return itr->second.emplace(name, callback).second;
}
