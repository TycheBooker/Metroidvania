#include "BaseAnimation.h"
#include "SpriteSheet.h"

BaseAnimation::BaseAnimation() :
	frameCurrent(0),
	frameStart(0),
	frameEnd(0),
	frameRow(0),
	frameTime(0.f),
	elapsedTime(0.f),
	frameActionStart(-1),
	frameActionEnd(-1),
	loop(false),
	playing(false)
{
}

BaseAnimation::~BaseAnimation()
{
}

void BaseAnimation::setSpriteSheet(SpriteSheet * sheet)
{
	spriteSheet = sheet;
}

void BaseAnimation::setFrame(const unsigned & frame)
{
	if ((frame >= frameStart && frame <= frameEnd) ||
		(frame >= frameEnd && frame <= frameStart)) {
		frameCurrent = frame;
	}
}

bool BaseAnimation::isInAction()
{
	if (frameActionEnd == -1 || frameActionEnd == -1) return true;

	return (frameCurrent >= frameActionStart && frameCurrent <= frameActionEnd);
}

void BaseAnimation::play()
{
	playing = true;
}

void BaseAnimation::pause()
{
	playing = false;
}

void BaseAnimation::stop()
{
	playing = false;
	reset();
}

void BaseAnimation::reset()
{
	frameCurrent = frameStart;
	elapsedTime = 0.f;
	cropSprite();
}

void BaseAnimation::setName(std::string name)
{
	this->name = name;
}

void BaseAnimation::setLooping(bool loop)
{
	this->loop = loop;
}

void BaseAnimation::update(const sf::Time & deltaTime)
{
	if (!playing) return;

	elapsedTime += deltaTime.asSeconds();
	if (elapsedTime < frameTime) return;

	frameStep();
	cropSprite();
	elapsedTime = 0.f;
}

std::stringstream & operator>>(std::stringstream & stream, BaseAnimation & animation)
{
	animation.readIn(stream);
	return stream;
}
