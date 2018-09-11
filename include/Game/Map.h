#pragma once
#include "SharedContext.h"
#include "TextureManager.h"

enum Sheet
{
    Tile_Size = 32,
    Sheet_Width = 256,
    Sheet_Height = 256
};

using TileID = unsigned;

struct TileInfo
{
    TileInfo(SharedContext* context, const std::string& texture = "", TileID id = 0) :
        context(context),
        id(0),
        deadly(false)
    {
        TextureManager* textureManager = context->textureManager;
        if (texture == "") {
            this->id = id;
            return;
        }

        if (!textureManager->requireResource(texture)) return;

        this->texture = texture;
        this->id = id;
        sprite.setTexture(*textureManager->getResource(texture));
        sf::IntRect tileBoundaries(id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
                                    id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
                                    Sheet::Tile_Size, Sheet::Tile_Size);
        sprite.setTextureRect(tileBoundaries);
    }
    ~TileInfo()
    {
        if (texture == "") return;
        context->textureManager->releaseResource(texture);
    }

    sf::Sprite sprite;
    TileID id;
    std::string name;
    sf::Vector2f friction;
    bool deadly;

    SharedContext* context;
    std::string texture;
};