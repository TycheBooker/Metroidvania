#pragma once
#include "TextureManager.h"
#include "Directions.h"
#include "BaseAnimation.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

using Animations = std::unordered_map<std::string, BaseAnimation*>;

class SpriteSheet
{
public:
	SpriteSheet(TextureManager * textureManager);
	~SpriteSheet();

	void cropSprite(const sf::IntRect& rect);
	void setSpriteSize(const sf::Vector2i& size);
	void setSpritePosition(const sf::Vector2f& position);
	void setDirection(const Direction& direction);

	bool loadSheet(const std::string& file);
	void releaseSheet();

	BaseAnimation* getCurrentAnimation();
	bool setAnimation(const std::string& name, const bool& play = false, const bool& loop = false);

	void update(const sf::Time& deltaTime);
	void draw(sf::RenderWindow * window);
private:
	std::string texture;
	sf::Sprite sprite;
	sf::Vector2i spriteSize;
	sf::Vector2f spriteScale;
	Direction direction;
	std::string animType;
	Animations animations;
	BaseAnimation* animationCurrent;
	TextureManager* textureManager;
};