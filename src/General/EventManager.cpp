#include "EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

EventManager::EventManager() : hasFocus(true)
{
    loadBindings();
}

EventManager::~EventManager()
{
    for (auto &itr : bindings) {
        delete itr.second;
        itr.second = nullptr;
    }
}

bool EventManager::addBinding(Binding *binding)
{
    if (bindings.find(binding->name) != bindings.end()) return false;

    return bindings.emplace(binding->name, binding).second;
}

bool EventManager::removeBinding(std::string name)
{
    auto itr = bindings.find(name);
    if (itr == bindings.end()) return false;

    delete itr->second;
    bindings.erase(itr);
    return true;
}

void EventManager::setCurrentState(StateType state)
{
	currentState = state;
}

void EventManager::setFocus(const bool &focus)
{
    hasFocus = focus;
}

bool EventManager::removeCallback(StateType state, const std::string &name)
{
    auto statesItr = callbacks.find(state);
    if (statesItr == callbacks.end()) return false;

    auto namesItr = statesItr->second.find(name);
    if (namesItr == statesItr->second.end()) return false;

	statesItr->second.erase(name);
    return true;
}

void EventManager::handleEvent(sf::Event &event)
{
    for (auto &bind_itr : bindings) {
        Binding *bind = bind_itr.second;
        for (auto &evenItr : bind->events) {
            EventType sfmlEvent = (EventType)event.type;
            if (evenItr.first != sfmlEvent) continue;

            if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
                if (evenItr.second.code == event.key.code) {
                    if (bind->details.keyCode != -1) {
                        bind->details.keyCode = evenItr.second.code;
                    }
                    ++(bind->count);
                    break;
                }
            }
            else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
                if (evenItr.second.code == event.mouseButton.button) {
                    bind->details.mouse.x = event.mouseButton.x;
                    bind->details.mouse.y = event.mouseButton.y;
                    if (bind->details.keyCode != -1) {
                        bind->details.keyCode = evenItr.second.code;
                    }
                    ++bind->count;
                    break;
                }
            }
            else {
                if (sfmlEvent == EventType::MouseWheel) {
                    bind->details.mouseWheelDelta = event.mouseWheel.delta;
                }
                else if (sfmlEvent == EventType::WindowResized) {
                    bind->details.size.x = event.size.width;
                    bind->details.size.y = event.size.height;
                }
                else if (sfmlEvent == EventType::TextEntered) {
                    bind->details.textEntered = event.text.unicode;
                }
                ++(bind->count);
            }
        }
    }
}

void EventManager::update()
{
    if (!hasFocus) return;

    for (auto &bind_itr : bindings) {
        Binding *bind = bind_itr.second;
        for (auto &eventItr : bind->events) {
            switch (eventItr.first) {
            case (EventType::Keyboard):
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(eventItr.second.code))) {
                    if (bind->details.keyCode != -1) {
                        bind->details.keyCode = eventItr.second.code;
                    }
                    ++(bind->count);
                }
                break;
            case (EventType::Mouse):
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button(eventItr.second.code))) {
                    if (bind->details.keyCode != -1) {
                        bind->details.keyCode = eventItr.second.code;
                    }
                    ++(bind->count);
                }
                break;
            case (EventType::Joystick):
                break;
            default:
                break;
            }
        }
        if (bind->events.size() == bind->count) {
            auto stateCallbacks = callbacks.find(currentState);
            auto otherCallbacks = callbacks.find(StateType(0));

            if (stateCallbacks != callbacks.end()) {
                auto callItr = stateCallbacks->second.find(bind->name);
                if (callItr != stateCallbacks->second.end()) {
                    callItr->second(&bind->details);
                }
            }

            if (otherCallbacks != callbacks.end()) {
                auto callItr = otherCallbacks->second.find(bind->name);
                if (callItr != otherCallbacks->second.end()) {
                    callItr->second(&bind->details);
                }
            }
        }
        bind->count = 0;
        bind->details.clear();
    }
}

sf::Vector2i EventManager::getMousePos(sf::RenderWindow *window)
{
    return (window ? sf::Mouse::getPosition(*window)
                   : sf::Mouse::getPosition());
}

void EventManager::loadBindings()
{
    std::string delimiter = ":";
    std::ifstream bindings;

    bindings.open("data/keys.cfg");
    if (!bindings.is_open()) {
        std::cout << "Failed loading keys.cfg!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(bindings, line)) {
        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;
        Binding *bind = new Binding(callbackName);

        while (!keystream.eof()) {
            std::string keyval;
            keystream >> keyval;
            int start = 0;
            int end = keyval.find(delimiter);
            if (end == std::string::npos) {
                delete bind;
                bind = nullptr;
                break;
            }

            EventType type = EventType(stoi(keyval.substr(start, end - start)));
            int code = stoi(keyval.substr(end + delimiter.length()));
            EventInfo eventInfo;
            eventInfo.code = code;

            bind->bindEvent(type, eventInfo);
        }

        if (!addBinding(bind)) delete bind;
        bind = nullptr;
    }
    bindings.close();
}
