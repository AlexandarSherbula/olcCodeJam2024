#include "Player.h"
#include "Game.h"
#include "Assets.h"

Player::Player()
{
	position = { 72.0f, 559.0f };
	mAcceleration = 0.046875f;
	mDeceleration = 0.5f;
	mGravityForce = 0.21875f;
	mJumpForce = 6.5f;
	
	mCanShoot = true;
	mBulletFrameCount = 0;

	hitbox.position = { mPointA.position.x, position.y - 20.0f };
	hitbox.size = { 21.0f, 52.5f };

	hit = false;
	tempInvicible = false;
	mTempInvicibleFrameCount = 0;
	mHitFrameCount = 0;

	mAlpha = 255;

	health = 5;

	SetAnimationState(AnimationState::IDLE);
}

Player::~Player()
{
}

void Player::Update()
{
	Movement();

	Shoot();

	HandleAnimation();

	for (Bullet& b : listBullets)
	{
		b.Update();

		b.HandleAnimation();
	}

	if (hit)
	{
		mHitFrameCount++;
		if (mHitFrameCount >= 30)
		{
			if (health != 0)
			{
				tempInvicible = true;
				hit = false;
				mHitFrameCount = 0;
			}
			else
			{
				death = true;
			}
			
		}
	}

	if (tempInvicible)
	{
		mTempInvicibleFrameCount++;
		
		if (mTempInvicibleFrameCount >= 120)
		{
			tempInvicible = false;
			mTempInvicibleFrameCount = 0;
			
		}
	}
	
	listBullets.remove_if([&](const Bullet& b) {return b.position.x > game->ScreenWidth() + game->camera.offset.x || b.position.x < game->camera.offset.x || b.remove; });	
}

void Player::Shoot()
{
	if (!hit)
	{
		if (game->GetMouse(0).bHeld && mCanShoot)
		{
			if (mJumped)
				SetAnimationState(AnimationState::JUMP_SHOOT);
			else
			{
				if (mAnimState == AnimationState::RUN)
					SetAnimationState(AnimationState::RUN_SHOOT);
				else if (mAnimState == AnimationState::WALK)
					SetAnimationState(AnimationState::WALK_SHOOT);
				else if (mAnimState == AnimationState::IDLE)
					SetAnimationState(AnimationState::SHOOT);
			}

			listBullets.push_back(Bullet(olc::vf2d(position.x + 15.0f * (int32_t)direction, position.y - 13.0f)));

			mBulletFrameCount = 15;
			mCanShoot = false;
		}
		else
		{
			if (!game->GetMouse(0).bHeld)
			{
				if (mAnimState == AnimationState::RUN_SHOOT)
					SetAnimationState(AnimationState::RUN);
				else if (mAnimState == AnimationState::WALK_SHOOT)
					SetAnimationState(AnimationState::WALK);
				else if (mAnimState == AnimationState::SHOOT)
					SetAnimationState(AnimationState::IDLE);
			}

			if (!mCanShoot)
			{
				mBulletFrameCount--;

				if (mBulletFrameCount <= 0)
					mCanShoot = true;
			}
		}
	}
}

void Player::Movement()
{
	if (!hit)
	{
		if (!game->GetKey(olc::SPACE).bHeld)
		{
			mCanJump = true;
		}

		if (game->GetKey(olc::SPACE).bHeld && !mJumped && mCanJump)
		{
			speed.y -= mJumpForce;

			mJumped = true;
			mCanJump = false;

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
						if (!mJumped && mAnimState != AnimationState::RUN_SHOOT)
							SetAnimationState(AnimationState::RUN);
					}
					else
					{
						if (!mJumped && mAnimState != AnimationState::WALK_SHOOT)
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
						if (!mJumped && mAnimState != AnimationState::RUN_SHOOT)
							SetAnimationState(AnimationState::RUN);
					}
					else
					{
						if (!mJumped && mAnimState != AnimationState::WALK_SHOOT)
							SetAnimationState(AnimationState::WALK);
					}
				}
			}
		}

		speed.x = mGroundSpeed;
	}

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
		mCurrentImage = 1;
		mAnimState = state;
		mFrameCount = 0;
	}	
}

void Player::HandleAnimation()
{
	if (mGroundSpeed == 0.0f && mAnimState != AnimationState::SHOOT && mAnimState != AnimationState::JUMP)
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
		case AnimationState::WALK: case AnimationState::WALK_SHOOT:
		{
			if (mAnimState == AnimationState::WALK)
				mAnimationName = "walk";
			else if (mAnimState == AnimationState::WALK_SHOOT)
				mAnimationName = "walk-shoot";

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
		case AnimationState::RUN: case AnimationState::RUN_SHOOT:
		{
			if (mAnimState == AnimationState::RUN)
				mAnimationName = "run";
			else if (mAnimState == AnimationState::RUN_SHOOT)
				mAnimationName = "run-shoot";
			
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
		case AnimationState::SHOOT:
		{
			mAnimationName = "shoot";

			break;
		}
		case AnimationState::JUMP_SHOOT:
		{
			mAnimationName = "jump-shoot";
			break;
		}
	}
}

void Player::UpdateSensors()
{
	mPointA.position = { position.x - 10.0f, position.y + 33.0f };
	mPointB.position = { position.x + 10.0f, position.y + 33.0f };

	hitbox.position = { mPointA.position.x, position.y - 20.0f };
}

void Player::Draw()
{
	olc::Decal* decal;
	if (hit)
	{
		decal = Assets::get().GetDecal("hurt");
	}
	else
	{
		if (mAnimState == AnimationState::SHOOT)
			decal = Assets::get().GetDecal(mAnimationName);
		else if (mAnimState == AnimationState::JUMP_SHOOT)
			decal = Assets::get().GetDecal("jump4");
		else
			decal = Assets::get().GetDecal(mAnimationName + std::to_string(mCurrentImage));
	}

	if (tempInvicible)
	{
		if (mTempInvicibleFrameCount % 2 == 0)
		{
			if (mAlpha == 255)
				mAlpha = 0;
			else
				mAlpha = 255;
		}
	}
	else
		mAlpha = 255;

	olc::vf2d drawPosition = { position.x - (decal->sprite->width / 2.0f) * (float)direction, position.y - decal->sprite->height / 2.0f};

	game->DrawDecal(drawPosition - game->camera.offset, decal, { (float)direction , 1.0f}, olc::Pixel(255, 255, 255, mAlpha));

	for (Bullet& b : listBullets)
	{
		b.Draw();
	}

	//game->FillRectDecal(position - game->camera.offset, { 1, 1 }, olc::BLACK);
	//game->FillRectDecal(olc::vf2d((position.x - 1), position.y) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d((position.x + 1), position.y) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d( position.x, position.y - 1 ) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d( position.x, position.y + 1 ) - game->camera.offset, { 1, 1 });
	//
	//DrawHitbox();
}

void Player::Reset()
{
	position.x = 72.0f;
	position.y = 559.0f;
	UpdateSensors();

	direction = Direction::RIGHT;

	mCanShoot = true;
	mBulletFrameCount = 0;

	hit = false;
	tempInvicible = false;
	mTempInvicibleFrameCount = 0;
	mHitFrameCount = 0;

	mAlpha = 255;

	health = 5;

	SetAnimationState(AnimationState::IDLE);
}

void Player::ResetSpeed()
{
	mGroundSpeed = 0.0f;
	speed.x = 0.0f;
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

	game->FillRectDecal(hitbox.position - game->camera.offset, hitbox.size, olc::Pixel(255, 0, 255, 125));
}
