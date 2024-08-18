#include "Game.h"
#include "Assets.h"

uint32_t increment = 1;

Game::Game()
{
	sAppName = "olcCodeJam2024";
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;
}

Game::~Game()
{
	
}

bool Game::OnUserCreate()
{
	Assets::get().LoadSprites();

	map.Load("assets/sprites/map01.png", "assets/nlohmann/json/olcCodeJam2024_map.json");

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	timer += fElapsedTime;

	while (fixedTimeSimulated < timer)
	{
		OnFixedUpdate();
		fixedTimeSimulated += 1.0f / 60.0f;
	}

	player.HandleAnimation(fElapsedTime);

	Clear(olc::VERY_DARK_BLUE);

	map.Draw();

	player.Draw();

	return !GetKey(olc::ESCAPE).bPressed;
}

void Game::OnFixedUpdate()
{
	player.Movement();
}
