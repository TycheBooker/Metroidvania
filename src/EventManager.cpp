#include "EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>


EventManager::EventManager() :
    m_hasFocus(true)
{
    loadBindings();
}

EventManager::~EventManager()
{
    for (auto & itr : m_bindings)
    {
        delete itr.second;
        itr.second = nullptr;
    }
}

bool EventManager::addBinding(Binding * t_binding)
{
    if (m_bindings.find(t_binding->m_name) != m_bindings.end())
    {
        return false;
    }
    return m_bindings.emplace(t_binding->m_name, t_binding).second;
}

bool EventManager::removeBinding(std::string t_name)
{
    auto itr = m_bindings.find(t_name);
    if (itr == m_bindings.end())
    {
        return false;
    }
    delete itr->second;
    m_bindings.erase(itr);
    return true;
}

void EventManager::setFocus(const bool & t_focus)
{
	m_hasFocus = t_focus;
}

void EventManager::removeCallback(const std::string & t_name)
{
    m_callbacks.erase(t_name);
}

void EventManager::handleEvent(sf::Event & t_event)
{
    for (auto & bind_itr : m_bindings)
    {
        Binding * bind = bind_itr.second;
        for (auto & event_itr : bind->m_events)
        {
            EventType sfmlEvent = (EventType)t_event.type;
            if (event_itr.first != sfmlEvent)
            {
                continue;
            }
            if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
            {
                if (event_itr.second.m_code == t_event.key.code)
                {
                    if (bind->m_details.m_keyCode != -1)
                    {
                        bind->m_details.m_keyCode = event_itr.second.m_code;
                    }
                    ++(bind->count);
                    break;
                }
            }
            else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
            {
                if (event_itr.second.m_code == t_event.mouseButton.button)
                {
                    bind->m_details.m_mouse.x = t_event.mouseButton.x;
                    bind->m_details.m_mouse.y = t_event.mouseButton.y;
                    if (bind->m_details.m_keyCode != -1)
                    {
                        bind->m_details.m_keyCode = event_itr.second.m_code;
                    }
                    ++bind->count;
                    break;
                }
            }
            else
            {
                if (sfmlEvent == EventType::MouseWheel)
                {
                    bind->m_details.m_mouseWheelDelta = t_event.mouseWheel.delta;
                }
                else if (sfmlEvent == EventType::WindowResized)
                {
                    bind->m_details.m_size.x = t_event.size.width;
                    bind->m_details.m_size.y = t_event.size.height;
                }
                else if (sfmlEvent == EventType::TextEntered)
                {
                    bind->m_details.m_textEntered = t_event.text.unicode;
                }
                ++(bind->count);
            }
        }
    }
}

void EventManager::update()
{
    if (!m_hasFocus)
    {
        return;
    }
    for (auto & bind_itr : m_bindings)
    {
        Binding * bind = bind_itr.second;
        for (auto & event_itr : bind->m_events)
        {
            switch (event_itr.first)
            {
                case (EventType::Keyboard):
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event_itr.second.m_code)))
                    {
                        if (bind->m_details.m_keyCode != -1)
                        {
                            bind->m_details.m_keyCode = event_itr.second.m_code;
                        }
                        ++(bind->count);
                    }
                    break;
                case (EventType::Mouse):
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button(event_itr.second.m_code)))
                    {
                        if (bind->m_details.m_keyCode != -1)
                        {
                            bind->m_details.m_keyCode = event_itr.second.m_code;
                        }
                        ++(bind->count);
                    }
                    break;
                case(EventType::Joystick):
                    break;
                default:
                    break;
            }
        }
        if (bind->m_events.size() == bind->count)
        {
            auto call_itr = m_callbacks.find(bind->m_name);
            if (call_itr != m_callbacks.end())
            {
                call_itr->second(&bind->m_details);
            }
        }
        bind->count = 0;
        bind->m_details.clear();
    }
}

sf::Vector2i EventManager::getMousePos(sf::RenderWindow *t_window)
{
    return (t_window ? sf::Mouse::getPosition(*t_window)
                     : sf::Mouse::getPosition());
}

void EventManager::loadBindings()
{
    std::string delimiter = ":";
    std::ifstream bindings;

    bindings.open("data/keys.cfg");
    if (!bindings.is_open())
    {
        std::cout << "Failed loading keys.cfg!" << std::endl;
        return;
    }

    std::string line;
    while(std::getline(bindings, line))
    {
        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;
        Binding * bind = new Binding(callbackName);

        while(!keystream.eof())
        {
            std::string keyval;
            keystream >> keyval;
            int start = 0;
            int end = keyval.find(delimiter);
            if (end == std::string::npos)
            {
                delete bind;
                bind = nullptr;
                break;
            }

            EventType type = EventType(stoi(keyval.substr(start, end - start)));
            int code = stoi(keyval.substr(end + delimiter.length()));
            EventInfo eventInfo;
            eventInfo.m_code = code;

            bind->bindEvent(type, eventInfo);
        }

        if (!addBinding(bind))
        {
            delete bind;
        }
        bind = nullptr;
    }
    bindings.close();
}
