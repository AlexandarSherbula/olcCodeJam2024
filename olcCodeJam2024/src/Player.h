#pragma once

#include "olcPixelGameEngine.h"

#include "Object.h"
#include "Map.h"

enum class State
{
	GROUND,
	AIR
};

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
public:
	AnchorPoint mPointA;
	AnchorPoint mPointB;
private:
	float mAcceleration;
	float mAirAcceleration;
	float mDeceleration;
	float mGroundSpeed;
	float mGravityForce;
	float mJumpForce;

	bool mJumped;
	bool mJumpLock;

	AnimationState mAnimState;
public:
	Player();
	~Player();

	void Movement();

	void SetAnimationState(AnimationState state);
	void HandleAnimation(float fElapsedTime) override;
	void Draw() override;
private:
	void UpdateSensors();
	void FindSurface(AnchorPoint& point);

	void DrawHitbox();
};