#pragma once

#include "olcPixelGameEngine.h"

#include "Object.h"
#include "Map.h"
#include "Bullet.h"

enum class State
{
	GROUND,
	AIR
};

enum class AnimationState
{
	IDLE,
	SHOOT,
	WALK,
	WALK_SHOOT,
	RUN,
	RUN_SHOOT,
	JUMP,
	JUMP_SHOOT,
	BACK_JUMP,
	HURT,
	CROUCH,
	CLIMB
};

class Player : public AnimatedObject
{
private:
	AnchorPoint mPointA;
	AnchorPoint mPointB;

	float mAcceleration;
	float mDeceleration;
	float mGroundSpeed;
	float mGravityForce;

	bool mJumped;
	bool mCanJump;
	float mJumpForce;

	AnimationState mAnimState;

	bool mCanShoot;
	int32_t mBulletFrameCount;
public:
	std::list<Bullet> listBullets;
public:
	Player();
	~Player();

	void Update() override;
	void Shoot();
	void Movement();

	void SetAnimationState(AnimationState state);
	void HandleAnimation() override;
	void Draw() override;
private:
	void UpdateSensors();
	void FindSurface(AnchorPoint& point);

	void DrawHitbox();
};