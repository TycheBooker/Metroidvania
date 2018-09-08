#pragma once
#include "ResourceManager.h"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager();
	~TextureManager();

	sf::Texture* load(const std::string& path);
};