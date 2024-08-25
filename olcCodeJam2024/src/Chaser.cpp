#include "Chaser.h"
#include "Game.h"
#include "Assets.h"

Chaser::Chaser()
{
}

Chaser::Chaser(const olc::vf2d& position, bool isFlipped)
{
	mHorizontalFlip = isFlipped;

	hitbox.size = { (float)Assets::get().GetDecal("v-yellow")->sprite->width, (float)Assets::get().GetDecal("v-yellow")->sprite->height};
	trigger.size = { 200.0f, (float)Assets::get().GetDecal("v-yellow")->sprite->height };

	this->position.x = (isFlipped) ? position.x + hitbox.size.x : position.x;
	this->position.y = position.y - hitbox.size.y;
	
	direction = (isFlipped) ? Direction::RIGHT : Direction::LEFT;

	hitbox.position.x = position.x;
	hitbox.position.y = position.y - hitbox.size.y;

	trigger.position.x = (isFlipped) ? position.x + hitbox.size.x : position.x - trigger.size.x; 
	trigger.position.y = this->position.y;

	drive = false;
	speed = { 0.0f, 0.0f };
}

void Chaser::Update()
{
	if (CheckCollision(game->player.hitbox, hitbox) && !game->player.tempInvicible)
		game->player.Hurt();

	if (CheckCollision(game->player.hitbox, trigger))
	{
		drive = true;
	}

	if (drive)
		speed.x += 0.046875f * (float)direction;
	
	position.x += speed.x;
	hitbox.position.x += speed.x;
}

void Chaser::Draw()
{
	olc::Decal* decal = Assets::get().GetDecal("v-yellow");

	game->DrawDecal(position - game->camera.offset, decal, { -(float)direction /*No idea why this has to be reverse*/, 1.0f});

	game->FillRectDecal(hitbox.position - game->camera.offset, hitbox.size, olc::Pixel(255, 0, 255, 125));

	game->FillRectDecal(trigger.position - game->camera.offset, trigger.size, olc::Pixel(255, 0, 0, 125));
}
