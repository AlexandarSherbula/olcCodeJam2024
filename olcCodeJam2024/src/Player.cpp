#include "Player.h"
#include "Game.h"
#include "Assets.h"

Player::Player()
{
	position = { 72.0f, 559.0f };
	mAcceleration = 0.046875f;
	mAirAcceleration = 0.093750f;
	mDeceleration = 0.5f;
	mGravityForce = 0.21875f;
	mJumpForce = 6.5f;
}

Player::~Player()
{
}

void Player::Movement()
{
	if (game->GetKey(olc::SPACE).bReleased)
	{
		mJumpLock = false;
	}

	if (game->GetKey(olc::SPACE).bHeld && !mJumped && !mJumpLock)
	{
		speed.y -= mJumpForce;

		mJumped = true;
		mJumpLock = true;

		SetAnimationState(AnimationState::JUMP);
	}

	if (game->GetKey(olc::SPACE).bReleased)
	{
		if (speed.y < -4.0f)
			speed.y = -4.0f;
	}

	if (game->GetKey(olc::A).bHeld == game->GetKey(olc::D).bHeld)
	{
		mGroundSpeed -= std::min(std::fabs(mGroundSpeed), 0.046875f) * ((mGroundSpeed > 0.0f) ? 1.0f : -1.0f);
	}
	else
	{
		if (game->GetKey(olc::A).bHeld)
		{
			if (mGroundSpeed > 0.0f)
			{
				mGroundSpeed -= mDeceleration;
				if (mGroundSpeed <= 0.0f)
				{
					mGroundSpeed = -mDeceleration;
				}
			}
			else
			{
				direction = Direction::LEFT;
				mGroundSpeed -= mAcceleration;
				if (mGroundSpeed <= -6.0f)
				{
					mGroundSpeed = -6.0f;
					if (!mJumped)
						SetAnimationState(AnimationState::RUN);
				}
				else
				{
					if (!mJumped)
						SetAnimationState(AnimationState::WALK);
				}
			}
		}
		if (game->GetKey(olc::D).bHeld)
		{
			if (mGroundSpeed < 0.0f)
			{
				mGroundSpeed += mDeceleration;
				if (mGroundSpeed >= 0.0f)
				{
					mGroundSpeed = mDeceleration;
				}
			}
			else
			{
				direction = Direction::RIGHT;
				mGroundSpeed += mAcceleration;
				if (mGroundSpeed >= 6.0f)
				{
					mGroundSpeed = 6.0f;
					if (!mJumped)
						SetAnimationState(AnimationState::RUN);
				}
				else
				{
					if (!mJumped)
						SetAnimationState(AnimationState::WALK);
				}
			}
		}
	}

	speed.x = mGroundSpeed;

	speed.y += mGravityForce;
	if (speed.y > 16.0f)
		speed.y = 16.0f;

	position += speed;

	if (speed.y >= 0.0f)
	{
		FindSurface(mPointA);
		FindSurface(mPointB);
	}

	UpdateSensors();
}

void Player::FindSurface(AnchorPoint& point)
{
	if (game->map.GetTileID(point.position / 16) == 272 || game->map.GetTileID(point.position / 16) == 273)
	{
		if (mJumped)
		{
			if (mGroundSpeed != 0.0f)
			{
				if (std::abs(mGroundSpeed) >= 6.0f)
					SetAnimationState(AnimationState::RUN);
				else
					SetAnimationState(AnimationState::WALK);
			}
			else
				SetAnimationState(AnimationState::IDLE);
			mJumped = false;
		}

		uint32_t unitPos = (point.position.y / 16);
		position.y = unitPos * 16.0f - 33.0f;
		speed.y = 0.0f;

		UpdateSensors();
	}
}

void Player::SetAnimationState(AnimationState state)
{
	if (mAnimState != state)
	{
		mAnimState = state;
		mCurrentImage = 1;
	}	
}

void Player::HandleAnimation(float fElapsedTime)
{
	if (mGroundSpeed == 0.0f)
		SetAnimationState(AnimationState::IDLE);

	switch (mAnimState)
	{
		case AnimationState::IDLE:
		{
			mAnimationName = "idle";
			mFirstImage = 1;
			mLastImage = 4;
	
			mMaxFrameCount = 5;

			if (mFrameCount >= mMaxFrameCount)
			{
				if (mCurrentImage >= mLastImage)
					mCurrentImage = mFirstImage;
				else
					mCurrentImage++;
				mFrameCount = 0;
			}
			else
				mFrameCount ++;

			break;
		}
		case AnimationState::WALK:
		{
			mAnimationName = "walk";
			mFirstImage = 1;
			mLastImage = 16;
	
			mMaxFrameCount = std::floor(std::max(0.0f, 8.0f - std::abs(mGroundSpeed)));

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

			break;
		}
		case AnimationState::RUN:
		{
			mAnimationName = "run";
			mFirstImage = 1;
			mLastImage = 8;

			mMaxFrameCount = 5;

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

			break;
		}
		case AnimationState::JUMP:
		{
			mAnimationName = "jump";
			mFirstImage = 1;
			mLastImage = 4;

			mMaxFrameCount = 5;

			if (mFrameCount >= mMaxFrameCount)
			{
				if (mCurrentImage < mLastImage)
					mCurrentImage++;
				mFrameCount = 0;
			}
			else
				mFrameCount++;

			break;
		}
	}
}

void Player::UpdateSensors()
{
	mPointA.position = { position.x - 10.0f, position.y + 33.0f };
	mPointB.position = { position.x + 10.0f, position.y + 33.0f };
}

void Player::Draw()
{
	olc::Decal* decal = Assets::get().GetDecal(mAnimationName + std::to_string(mCurrentImage));
	olc::vf2d drawPosition = { position.x - (decal->sprite->width / 2.0f) * (float)direction, position.y - decal->sprite->height / 2.0f };

	game->DrawDecal(drawPosition - game->camera.offset, decal, { (float)direction , 1.0f});

	//game->FillRectDecal(position - game->camera.offset, { 1, 1 }, olc::BLACK);
	//game->FillRectDecal(olc::vf2d((position.x - 1), position.y) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d((position.x + 1), position.y) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d( position.x, position.y - 1 ) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d( position.x, position.y + 1 ) - game->camera.offset, { 1, 1 });

	//DrawHitbox();
}

void Player::DrawHitbox()
{
	if (speed.y >= 0.0f)
	{
		game->FillRectDecal(olc::vf2d(mPointA.position.x, position.y) - game->camera.offset, { 1.0f, 33.0f }, olc::RED);
		game->FillRectDecal(olc::vf2d(mPointB.position.x, position.y) - game->camera.offset, { 1.0f, 33.0f }, olc::BLUE);

		game->FillRectDecal(mPointA.position - game->camera.offset, { 1.0f, 1.0f });
		game->FillRectDecal(mPointB.position - game->camera.offset, { 1.0f, 1.0f });
	}	
}
