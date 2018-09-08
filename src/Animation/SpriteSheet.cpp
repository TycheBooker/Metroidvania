#include "SpriteSheet.h"
#include <iostream>

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

sf::Vector2i SpriteSheet::getSpriteSize() const
{
	return spriteSize;
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

Direction SpriteSheet::getDirection() const
{
	return direction;
}

bool SpriteSheet::loadSheet(const std::string & file)
{
	std::ifstream sheet;
	//sheet.open(Utils::getWorkingDirectory() + file);
	sheet.open(file);
	if (sheet.is_open()) {
		releaseSheet();
		std::string line;
		while (std::getline(sheet, line)) {
			if (line[0] == '|') continue;

			std::stringstream keystream(line);
			std::string type;
			keystream >> type;

			if (type == "Texture") {
				if (this->texture != "") {
					std::cerr << "Duplicate texture entries in: " << file << std::endl;
					continue;
				}

				std::string texture;
				keystream >> texture;
				if (!textureManager->requireResource(texture)) {
					std::cerr << "Could not set up the texture: " << texture << std::endl;
					continue;
				}

				this->texture = texture;
				sprite.setTexture(*textureManager->getResource(this->texture));
			}
			else if (type == "Size") {
				keystream >> spriteSize.x >> spriteSize.y;
				setSpriteSize(spriteSize);
			}
			else if (type == "Scale") {
				keystream >> spriteScale.x >> spriteScale.y;
				sprite.setScale(spriteScale);
			}
			else if (type == "AnimationType") {
				keystream >> animType;
			}
			else if (type == "Animation") {
				std::string name;
				keystream >> name;
				if (animations.find(name) != animations.end()) {
					std::cerr << "Duplicate animation(" << name << ") in:" << file << std::endl;
					continue;
				}

				BaseAnimation* animation = nullptr;
				if (animType == "Directional") {
					animation = new DirectionalAnimation();
				}
				else {
					std::cerr << "Unknown animation type: " << animType << " !" << std::endl;
					continue;
				}

				keystream >> *animation;
				animation->setSpriteSheet(this);
				animation->setName(name);
				animation->reset();
				animations.emplace(name, animation);

				if (animationCurrent) continue;

				animationCurrent = animation;
				animationCurrent->play();
			}
		}
		sheet.close();
		return true;
	}
	std::cerr << "Failed loading spritesheet: " << file << " !" << std::endl;
	return false;
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
