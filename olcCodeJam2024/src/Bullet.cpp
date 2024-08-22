#include "Bullet.h"
#include "Game.h"
#include "Assets.h"

Bullet::Bullet()
{
}

Bullet::Bullet(const olc::vf2d& position, const olc::Pixel& colorTint)
{
	this->position = position;
	mColorTint = colorTint;
	direction = game->player.direction;
	mFirstImage = 1;
	mLastImage = 3;
	mMaxFrameCount = 5;

	hitbox.size = { (float)Assets::get().GetDecal("shot1")->sprite->width, (float)Assets::get().GetDecal("shot1")->sprite->height };

	remove = false;
}

void Bullet::Update()
{
	Travel();

	HandleAnimation();
}

void Bullet::Travel()
{
	position.x += 10.0f * (int32_t)direction;

	hitbox.position.x = (direction == Direction::LEFT) ? position.x - hitbox.size.x : position.x;
	hitbox.position.y = position.y;
}

void Bullet::HandleAnimation()
{
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

void Bullet::Draw()
{
	game->DrawDecal(position - game->camera.offset, Assets::get().GetDecal("shot" + std::to_string(mCurrentImage)), { (float)direction, 1.0f}, mColorTint);

	//game->FillRectDecal(hitbox.position - game->camera.offset, hitbox.size, olc::Pixel(255, 0, 255, 125));
}
