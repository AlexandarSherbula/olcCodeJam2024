#include "Player.h"
#include "Game.h"
#include "Assets.h"

Player::Player()
{
	position = { 320.0f, 180.0f };
	mAcceleration = 0.046875f;
	mAirAcceleration = 0.093750f;
}

Player::~Player()
{
}

void Player::Movement()
{
	if (mGroundSpeed == 0.0f)
		SetAnimationState(AnimationState::IDLE);

	if (game->GetKey(olc::A).bHeld == game->GetKey(olc::D).bHeld)
	{
		mGroundSpeed -= std::min(std::fabs(mGroundSpeed), 0.046875f) * ((mGroundSpeed > 0.0f) ? 1.0f : -1.0f);
	}
	if (game->GetKey(olc::A).bHeld)
	{
		direction = Direction::LEFT;
		SetAnimationState(AnimationState::WALK);
		mGroundSpeed -= mAcceleration;
		if (mGroundSpeed <= -6.0f)
			mGroundSpeed = -6.0f;
	}
	if (game->GetKey(olc::D).bHeld)
	{
		direction = Direction::RIGHT;
		SetAnimationState(AnimationState::WALK);
		mGroundSpeed += mAcceleration;
		if (mGroundSpeed >= 6.0f)
			mGroundSpeed = 6.0f;
	}

	speed.x = mGroundSpeed;

	position.x += speed.x;

	
}

void Player::SetAnimationState(AnimationState state)
{
	if (mAnimState != state)
	{
		mAnimState = state;
		mCurrentImage = 1;
	}
	
}

void Player::HandleAnimation()
{
	switch (mAnimState)
	{
		case AnimationState::IDLE:
		{
			mAnimationName = "idle";
			mFirstImage = 1;
			mLastImage = 4;
	
			mMaxFrameCount = 6;
			break;
		}
		case AnimationState::WALK:
		{
			mAnimationName = "walk";
			mFirstImage = 1;
			mLastImage = 16;
	
			mMaxFrameCount = 6;
			break;
		}
	}
	
	if (mFrameCount >= mMaxFrameCount)
	{
		if (mCurrentImage >= mLastImage)
			mCurrentImage = mFirstImage;
		else
			mCurrentImage++;
		mFrameCount = 0;
	}
	else
		mFrameCount++;
}

void Player::Draw()
{
	olc::Decal* decal = Assets::get().GetDecal(mAnimationName + std::to_string(mCurrentImage));
	olc::vf2d drawPosition = { position.x - (decal->sprite->width / 2.0f) * (float)direction, position.y - decal->sprite->height / 2.0f };

	game->DrawDecal(drawPosition, decal, { (float)direction , 1.0f});
	game->FillRectDecal(position, { 1, 1 });
}
