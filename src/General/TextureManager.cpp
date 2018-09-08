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
	if (!texture)->loadFromFile(Utils::getWorkingDirectory() + path) {
		delete texture;
		texture = nullptr;
		std::cerr << "Failed to load texture: " << t_path << " !" << std::endl;
	}
	return texture;
}
