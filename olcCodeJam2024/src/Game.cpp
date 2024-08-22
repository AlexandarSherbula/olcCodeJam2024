#include "Game.h"
#include "Assets.h"

Game::Game()
{
	sAppName = "olcCodeJam2024";
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;
	shotSpeed = 0.0f;
}

Game::~Game()
{
	
}

bool Game::OnUserCreate()
{
	Assets::get().LoadSprites();
	song1 = ma.LoadSound("assets/sfx/The Toadz - Street Chase - Loop.mp3");

	camera.Create();

	map.Load("assets/sprites/map01.png", "assets/json/olcCodeJam2024_map.json");

	return true;
}

void Game::OnFixedUpdate()
{
	player.Update();

	camera.Update();
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	timer += fElapsedTime;

	while (fixedTimeSimulated < timer)
	{
		OnFixedUpdate();
		fixedTimeSimulated += 1.0f / 60.0f;
	}

	Clear(olc::VERY_DARK_BLUE);

	map.Draw();
	
	player.Draw();

	return !GetKey(olc::ESCAPE).bPressed;
}


