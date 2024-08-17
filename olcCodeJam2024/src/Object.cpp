#include "Object.h"

Object::Object()
{
}

Object::Object(const olc::vf2d& position)
{
}

void Object::Draw()
{
}

AnimatedObject::AnimatedObject() : Object()
{
	mAnimationName = "Unknown";
	mFirstImage = 1;
	mLastImage = 1;
	mCurrentImage = 1;
	mFrameCount = 0;

	direction = Direction::RIGHT;
}

void AnimatedObject::HandleAnimation()
{
}