#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(TextureManager * textureManager) :
	textureManager(textureManager),
	animationCurrent(nullptr),
	spriteScale(1.f, 1.f),
	direction(Direction::Right)
{
}

SpriteSheet::~SpriteSheet()
{
	releaseSheet();
}

void SpriteSheet::cropSprite(const sf::IntRect & rect)
{
	sprite.setTextureRect(rect);
}

void SpriteSheet::setSpriteSize(const sf::Vector2i & size)
{
	spriteSize = size;
	sprite.setOrigin(spriteSize.x / 2, spriteSize.y);
}

void SpriteSheet::setSpritePosition(const sf::Vector2f & position)
{
	sprite.setPosition(position);
}

void SpriteSheet::setDirection(const Direction & direction)
{
	if (direction == this->direction) return;
	this->direction = direction;
	animationCurrent->cropSprite();
}

void SpriteSheet::releaseSheet()
{
	textureManager->releaseResource(texture);
	animationCurrent = nullptr;
	while (animations.begin() != animations.end()) {
		delete animations.begin()->second;
		animations.erase(animations.begin());
	}
}

BaseAnimation * SpriteSheet::getCurrentAnimation()
{
	return animationCurrent;
}

bool SpriteSheet::setAnimation(const std::string & name, const bool & play, const bool & loop)
{
	auto itr = animations.find(name);
	if (itr == animations.end()) return false;
	if (itr->second == animationCurrent) return false;

	if (animationCurrent) {
		animationCurrent->stop();
	}
	animationCurrent = itr->second;
	animationCurrent->setLooping(loop);
	if (play) {
		animationCurrent->play();
	}
	animationCurrent->cropSprite();
	return true;
}

void SpriteSheet::update(const sf::Time & deltaTime)
{
	animationCurrent->update(deltaTime);
}

void SpriteSheet::draw(sf::RenderWindow * window)
{
	window->draw(sprite);
}
