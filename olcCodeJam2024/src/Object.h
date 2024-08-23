#pragma once

#include "olcPixelGameEngine.h"

enum class Direction
{
	LEFT = -1,
	RIGHT = 1
};

class AnchorPoint
{
public:
	olc::vi2d direction;
	olc::vf2d position;
	float distance;
public:
	AnchorPoint();
	AnchorPoint(const olc::vi2d& direction);
};

struct HitBox
{
	float widthRad;
	float heightRad;
	olc::vf2d position;
	olc::vf2d size;
};

class Object
{
public:
	olc::vf2d position;
	olc::vf2d speed;
	Direction direction;
	HitBox hitbox;
public:
	Object();
	Object(const olc::vf2d& position);

	virtual void Update();

	virtual void Draw();
};

class AnimatedObject : public Object
{
protected:
	int8_t mFirstImage;
	int8_t mLastImage;
	int8_t mCurrentImage;
	std::string mAnimationName;

	int8_t mFrameCount;
	int8_t mMaxFrameCount;
public:
	AnimatedObject();

	virtual void HandleAnimation();

	virtual void Reset();
};

bool CheckCollision(HitBox& one, HitBox& two);