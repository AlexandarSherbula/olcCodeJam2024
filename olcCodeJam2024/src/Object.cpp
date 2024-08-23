#include "Object.h"

Object::Object()
{
}

Object::Object(const olc::vf2d& position)
{
}

void Object::Update()
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
	mFrameCount = 0.0f;
	mMaxFrameCount = 1.0f;

	direction = Direction::RIGHT;
}

void AnimatedObject::HandleAnimation()
{
}

void AnimatedObject::Reset()
{
}


AnchorPoint::AnchorPoint()
{
}

AnchorPoint::AnchorPoint(const olc::vi2d& direction)
{
	this->direction = direction;
	position = { 0.0f, 0.0f };
	distance = 0.0f;
}

bool CheckCollision(HitBox& one, HitBox& two)
{
	bool collisionX = one.position.x + one.size.x >= two.position.x &&
		two.position.x + two.size.x >= one.position.x;

	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;

	return collisionX && collisionY;
}
