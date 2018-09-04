#pragma once
#include "Window.h"
#include "EventManager.h"

struct SharedContext
{
    SharedContext() : window(nullptr), eventManager(nullptr) {}
    Window *window;
    EventManager *eventManager;
};