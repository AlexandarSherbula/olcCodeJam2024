#include "GoalVehicle.h"
#include "Game.h"
#include "Assets.h"

GoalVehicle::GoalVehicle()
{
}

GoalVehicle::GoalVehicle(const olc::vf2d& position)
{
	this->position.x = position.x + Assets::get().GetDecal("v-red")->sprite->width;
	this->position.y = position.y - Assets::get().GetDecal("v-red")->sprite->height;

	hitbox.position.x = position.x;
	hitbox.position.y = position.y - Assets::get().GetDecal("v-red")->sprite->height;

	hitbox.size = { (float)Assets::get().GetDecal("v-red")->sprite->width, (float)Assets::get().GetDecal("v-red")->sprite->height };

	speed = { 0.0f, 0.0f };

	mVelocity = 0.046875f;

	mPlaceVictoryText = false;
}

void GoalVehicle::Update()
{
	if (CheckCollision(game->player.hitbox, this->hitbox))
	{
		if (game->GetKey(olc::W).bHeld)
			game->victory = true;
	}

	if (game->victory)
	{
		speed.x += mVelocity;
		speed.y -= mVelocity;

		position += speed;

		if (position.x >= game->map.size.x + 240.0f)
			mPlaceVictoryText = true;
	}
}

void GoalVehicle::Draw()
{
	game->DrawDecal(position - game->camera.offset, Assets::get().GetDecal("v-red"), {-1.0f, 1.0f});

	if (CheckCollision(game->player.hitbox, this->hitbox) && !game->victory)
	{
		std::string text = "Press 'W' to escape.";
		
		game->DrawStringDecal({ game->ScreenWidth() / 2.0f - (text.size() / 2.0f) * 16.0f, game->ScreenHeight() - 24.0f }, text, olc::WHITE, { 2.0f, 2.0f });
	}

	if (mPlaceVictoryText)
	{
		std::string text = "VICTORY!!";

		game->DrawStringDecal({ game->ScreenWidth() / 2.0f - (text.size() / 2.0f) * 16.0f, game->ScreenHeight() / 2.0f - 8.0f }, text, olc::WHITE, { 2.0f, 2.0f });
	}
}
