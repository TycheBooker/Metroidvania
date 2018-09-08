#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager();
	~TextureManager();

	sf::Texture* load(const std::string& path);
};