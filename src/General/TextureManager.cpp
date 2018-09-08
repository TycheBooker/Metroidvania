#include <iostream>
#include "TextureManager.h"

TextureManager::TextureManager() :
	ResourceManager("data/configs/textures.cgf")
{
}

TextureManager::~TextureManager()
{
}

sf::Texture * TextureManager::load(const std::string & path)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture) {
		//texture->loadFromFile(Utils::getWorkingDirectory() + path);
		texture->loadFromFile(path);
		delete texture;
		texture = nullptr;
		std::cerr << "Failed to load texture: " << path << " !" << std::endl;
	}
	return texture;
}
