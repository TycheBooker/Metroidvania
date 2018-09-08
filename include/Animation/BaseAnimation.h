#pragma once
#include <SFML/System.hpp>

class SpriteSheet;
using Frame = unsigned;

class BaseAnimation
{
	friend class SpriteSheet;
public:
	BaseAnimation();
	virtual ~BaseAnimation();

	void setSpriteSheet(SpriteSheet* sheet);
	void setFrame(const unsigned& frame);

	bool isInAction();

	void play();
	void pause();
	void stop();
	void reset();

	void setName(std::string name);
	void setLooping(bool loop);

	virtual void update(const sf::Time& deltaTime);

	friend std::stringstream& operator >>(std::stringstream& stream, BaseAnimation& animation);
protected:
	virtual void frameStep() = 0;
	virtual void cropSprite() = 0;
	virtual void readIn(std::stringstream& stream) = 0;

	Frame frameCurrent;
	Frame frameStart;
	Frame frameEnd;
	Frame frameRow;

	int frameActionStart;
	int frameActionEnd;

	float frameTime;
	float elapsedTime;

	bool loop;
	bool playing;

	std::string name;
	SpriteSheet* spriteSheet;
};