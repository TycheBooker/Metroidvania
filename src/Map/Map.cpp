#include "Map.h"
#include "StateManager.h"

Map::Map(SharedContext* context, BaseState* currentState) :
    context(context),
    defaultTile(context),
    maxMapSize(32, 32),
    tileCount(0),
    tileSetCount(0),
    mapGravity(512.f),
    loadNextMap(false),
    currentState(currentState)
{
    window = constext->window->getRenderWindow();
    context->gameMap = this;
    loadTiles("tiles,cfg");
}

Map::~Map()
{
    purgeMap();
    purgeTileSet();
    context->gameMap = nullptr;
}

Tile* Map::getTile(unsigned x, unsigned y)
{
    auto itr = tileMap.find(convertCoords(x, y));
    return (itr != tileMap.end() ? itr->second : nullptr);
}

unsigned Map::convertCoords(unsigned x, unsigned y)
{
    return (x * maxMapSize.x) + y;
}

void Map::update(sf::Time deltaTime)
{
    if (loadNextMap) {
        purgeMap();
        loadNextMap = false;
        if (nextMap != "") {
            loadMap("data/maps/" + nextMap);
        }
        else {
            currentState->getStateManager()->switchTo(StateType::GameOver);
        }
        nextMap = "";
    }
    sf::FloatRect viewSpace = context->window->getViewSpace();
    background.setPosition(viewSpace.left, viewSpace.top);
}

void Map::draw()
{
    window->draw(background);
    sf::FloatRect viewSpace = context->window->getViewSpace();

    sf::Vector2i tileBegin(
        floor(viewSpace.left / Sheet::Tile_Size),
        floor(viewSpace.top / Sheet::Tile_Size)
    );
    sf::Vector2i tileEnd(
        ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
        ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size)
    );

    unsigned count = 0;

    for(size_t x = tileBegin.x; x <= tileEnd.x; x++)
    {
        for(size_t y = tileBegin.y; y < tileEnd.y; y++)
        {
            if (x < 0 || y < 0) continue;
            Tile* tile = getTile(x, y);
            if (!tile) continue;

            sf::Sprite& sprite = tile->properties->sprite;
            sprite.setPosition(x * Sheet::Tile_Size, y* Sheet::Tile_Size);
            window->draw(sprite);
            count++;
        }
    }
}

void Map::purgeMap()
{
    tileCount = 0;
    for (auto &itr : tileMap) {
        delete itr.second;
    }
    tileMap.clear();
    context->entityManager->purge();

    if (backgroundTexture == "") return;
    context->textureManager->releaseResource(backgroundTexture);
    backgroundTexture = "";
}

void Map::purgeTileSet()
{
    for (auto &itr : tileSet) {
        delete itr.second;
    }
    tileSet.clear();
    tileSetCount = 0;
}

void Map::loadTiles(const std::string& path)
{
    std::ifstream file;
    // file.open(Utils::getWorkingDirectory() + path);
    file.open(path);
    if (!file.is_open()) {
        std::cout << "Failed loading tile set file: " << path << " !" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == '|') continue;
        std::stringstream keystream(line);
        int tileId;
        keystream >> tileId;
        if (tileId < 0) continue;

        TileInfo* tile = new TileInfo(context, "TileSheet", tileId);
        keystream >> tile->name >> tile->friction.x >> tile->friction.y >> tile->deadly;

        if (!tileSet.emplace(tileId, tile).second) {
            std::cout << "Duplicate tile type: " << tile->name >> " !" << std::endl;
            delete tile;
        }
    }
    file.close();
}