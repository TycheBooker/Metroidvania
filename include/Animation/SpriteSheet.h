#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Directions.h"
#include "BaseAnimation.h"
#include "DirectionalAnimation.h"

using Animations = std::unordered_map<std::string, BaseAnimation*>;

class SpriteSheet
{
public:
	SpriteSheet(TextureManager * textureManager);
	~SpriteSheet();

	void cropSprite(const sf::IntRect& rect);
	void setSpriteSize(const sf::Vector2i& size);
	sf::Vector2i getSpriteSize() const;
	void setSpritePosition(const sf::Vector2f& position);
	void setDirection(const Direction& direction);
	Direction getDirection() const;

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