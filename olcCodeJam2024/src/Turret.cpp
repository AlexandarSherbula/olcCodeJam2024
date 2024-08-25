#include "Turret.h"
#include "Game.h"
#include "Assets.h"

Turret::Turret()
{
}

Turret::Turret(const olc::vf2d& position)
{
	this->position.x = position.x;
	this->position.y = position.y - Assets::get().GetDecal("turret")->sprite->height;

	hitbox.position.x = position.x;
	hitbox.position.y = position.y - Assets::get().GetDecal("turret")->sprite->height;

	hitbox.size = { (float)Assets::get().GetDecal("turret")->sprite->width, (float)Assets::get().GetDecal("turret")->sprite->height };

	fireHitbox.size.x = 200.0f;
	fireHitbox.size.y = Assets::get().GetDecal("turret")->sprite->height;

	fireHitbox.position.x = this->position.x - fireHitbox.size.x;
	fireHitbox.position.y = this->position.y;

	destroyed = false;
	remove = false;

	countdownToFire = 0;
}

void Turret::Update()
{
	if (destroyed)
		HandleAnimation();
	else
	{
		if (CheckCollision(game->player.hitbox, fireHitbox))
		{
			if (countdownToFire == 60)
			{
				game->ma.Play(game->enemyShootSound);
				listBullets.push_back(Bullet(olc::vf2d(position.x - 15.0f, position.y)));
				countdownToFire = 0;
			}
			else
				countdownToFire++;
		}
	}

	for (Bullet& b : listBullets)
	{
		b.Update();

		b.HandleAnimation();
	}

	listBullets.remove_if([&](const Bullet& b) {return b.position.x > game->ScreenWidth() + game->camera.offset.x || b.position.x < game->camera.offset.x || b.remove; });
}

void Turret::HandleAnimation()
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

void Turret::Draw()
{
	olc::Decal* decal = Assets::get().GetDecal("turret");
	olc::vf2d drawingPosition = position;
	if (destroyed)
	{
		decal = Assets::get().GetDecal("enemy-explosion" + std::to_string(mCurrentImage));
		drawingPosition.x = position.x - Assets::get().GetDecal("turret")->sprite->width / 2.0f;
		drawingPosition.y = position.y - Assets::get().GetDecal("turret")->sprite->height / 2.0f;
	}

	game->DrawDecal(drawingPosition - game->camera.offset, decal, { 1.0f, 1.0f });

	game->FillRectDecal(hitbox.position - game->camera.offset, hitbox.size, olc::Pixel(255, 0, 255, 125));

	//game->FillRectDecal(fireHitbox.position - game->camera.offset, fireHitbox.size, olc::Pixel(255, 0, 0, 125));

	for (Bullet& b : listBullets)
	{
		b.Draw();
	}
}
