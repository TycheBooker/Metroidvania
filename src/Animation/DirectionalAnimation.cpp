#include "DirectionalAnimation.h"
#include "SpriteSheet.h"

void DirectionalAnimation::frameStep()
{
	if (frameStart < frameEnd) {
		frameCurrent++;
	}
	else {
		frameCurrent--;
	}

	if ((frameStart < frameEnd && frameCurrent > frameEnd) ||
		(frameStart > frameEnd && frameCurrent < frameEnd)) {
		if (loop) {
			frameCurrent = frameStart;
			return;
		}

		frameCurrent = frameEnd;
		pause();
	}
}

void DirectionalAnimation::cropSprite()
{
	sf::IntRect rect(
		spriteSheet->getSpriteSize().x * frameCurrent,
		spriteSheet->getSpriteSize().y * (frameRow + (short)spriteSheet->getDirection()),
		spriteSheet->getSpriteSize().x,
		spriteSheet->getSpriteSize().y);
	spriteSheet->cropSprite(rect);
}

void DirectionalAnimation::readIn(std::stringstream & stream)
{
	stream >> frameStart >> frameEnd >> frameRow >> frameTime >> frameActionStart >> frameActionEnd;
}
