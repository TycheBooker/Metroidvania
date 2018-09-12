#pragma once
#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"

class Map;
struct SharedContext
{
    SharedContext() :
        window(nullptr),
        eventManager(nullptr),
        textureManager(nullptr),
        gameMap(nullptr)
    {
    }
    Window* window;
    EventManager* eventManager;
    TextureManager* textureManager;
    Map* gameMap;
};