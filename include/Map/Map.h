#pragma once
#include "Tiles.h"
#include "BaseState.h"

using TileMap = std::unordered_map<TileID, Tile*>;
using TileSet = std::unordered_map<TileID, TileInfo*>;

class Map
{
public:
    Map(SharedContext* context, BaseState* currentState);
    ~Map();

    Tile* getTile(unsigned x, unsigned y);
    TileInfo* getDefaultTile();

    float getGravity() const;
    unsigned getTileSize() const;

    const sf::Vector2u& getMapSize() const;
    const sf::Vector2f& getPlayerStart() const;

    void loadMap(const std::string& path);
    void loadNext();
    void update(sf::Time deltaTime);
    void draw();
private:
    unsigned convertCoords(unsigned x, unsigned y);
    void loadTiles(const std::string& path);
    void purgeMap();
    void purgeTileSet();

    TileSet tileSet;
    TileMap tileMap;
    sf::Sprite background;
    TileInfo defaultTile;
    sf::Vector2u maxMapSize;
    sf::Vector2f playerStart;
    unsigned tileCount;
    unsigned tileSetCount;
    float mapGravity;
    std::string nextMap;
    bool loadNextMap;
    std::string backgroundTexture;
    BaseState* currentState;
    SharedContext* context;
    sf::RenderWindow* window;
};
