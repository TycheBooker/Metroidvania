#pragma once
#include "BaseAnimation.h"

class DirectionalAnimation : public BaseAnimation
{
protected:
	void frameStep();
	void cropSprite();
	void readIn(std::stringstream& stream);
};
