#pragma once

#include "olcPixelGameEngine.h"

#include "Object.h"

enum class AnimationState
{
	IDLE,
	WALK,
	SHOOT,
	RUN,
	RUN_SHOOT,
	JUMP,
	BACK_JUMP,
	HURT,
	CROUCH,
	CLIMB
};

class Player : public AnimatedObject
{
private:
	float mAcceleration;
	float mAirAcceleration;
	float mGroundSpeed;

	AnimationState mAnimState;
public:
	Player();
	~Player();

	void Movement();

	void SetAnimationState(AnimationState state);
	void HandleAnimation() override;
	void Draw() override;
};