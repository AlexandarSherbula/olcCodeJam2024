#pragma once

#include "olcPixelGameEngine.h"

enum class Direction
{
	LEFT = -1,
	RIGHT = 1
};

class Object
{
public:
	olc::vf2d position;
	olc::vf2d speed;
	Direction direction;
public:
	Object();
	Object(const olc::vf2d& position);

	virtual void Draw();
};

class AnimatedObject : public Object
{
protected:
	int8_t mFirstImage;
	int8_t mLastImage;
	int8_t mCurrentImage;
	std::string mAnimationName;

	uint8_t mFrameCount;
	uint8_t mMaxFrameCount;
public:
	AnimatedObject();

	virtual void HandleAnimation();
};