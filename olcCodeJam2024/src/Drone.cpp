#include "Drone.h"
#include "Game.h"
#include "Assets.h"

Drone::Drone()
{
}

Drone::Drone(const olc::vf2d& position)
{
	this->position = position;

	hitbox.size = { (float)Assets::get().GetDecal("drone1")->sprite->width - 20.0f, (float)Assets::get().GetDecal("drone1")->sprite->height };

	direction = Direction::RIGHT;
	mRotateAnimation = false;
	destroyed = false;
	remove = false;

	mAnimationName = "drone";
}

void Drone::Update()
{
	if (!destroyed)
	{
		mSpeed = 2 * std::cosf(game->timer);
		position.x += mSpeed;
	}

	if (std::abs(mSpeed) < 0.05f)
		mRotateAnimation = true;

	if (mRotateAnimation || destroyed)
		HandleAnimation();

	hitbox.position = olc::vf2d(position.x - (Assets::get().GetDecal("drone1")->sprite->width / 2.0f) + 10.0f, position.y - Assets::get().GetDecal("drone1")->sprite->height / 2.0f);
}

void Drone::HandleAnimation()
{
	if (destroyed)
	{
		mAnimationName = "enemy-explosion";
		mFirstImage = 1;
		mLastImage = 6;

		mMaxFrameCount = 5;

		if (mFrameCount >= mMaxFrameCount)
		{
			if (mCurrentImage >= mLastImage)
				remove = true;
			else
				mCurrentImage++;
			mFrameCount = 0;
		}
		else
			mFrameCount++;
	}
	else
	{
		mAnimationName = "drone";
		mFirstImage = 1;
		mLastImage = 4;

		mMaxFrameCount = 5;

		if (mFrameCount >= mMaxFrameCount)
		{
			if (mCurrentImage >= mLastImage)
			{
				if (direction == Direction::LEFT)
					direction = Direction::RIGHT;
				else
					direction = Direction::LEFT;

				mCurrentImage = mFirstImage;
				mRotateAnimation = false;
			}
			else
				mCurrentImage++;
			mFrameCount = 0;
		}
		else
			mFrameCount++;
	}
	
}

void Drone::Draw()
{
	olc::Decal* decal = Assets::get().GetDecal(mAnimationName + std::to_string(mCurrentImage));

	olc::vf2d drawPosition = { position.x + (decal->sprite->width / 2.0f) * (float)direction, position.y - decal->sprite->height / 2.0f };

	game->DrawDecal(drawPosition - game->camera.offset, decal, {-(float)direction, 1.0f});

	//game->FillRectDecal(position - game->camera.offset, { 1, 1 }, olc::BLACK);
	//game->FillRectDecal(olc::vf2d((position.x - 1), position.y) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d((position.x + 1), position.y) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d(position.x, position.y - 1) - game->camera.offset, { 1, 1 });
	//game->FillRectDecal(olc::vf2d(position.x, position.y + 1) - game->camera.offset, { 1, 1 });

	//game->FillRectDecal(hitbox.position - game->camera.offset, hitbox.size, olc::Pixel(255, 0, 255, 125));

}
