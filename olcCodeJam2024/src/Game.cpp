#include "Game.h"
#include "Assets.h"

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
	song1 = ma.LoadSound("assets/sfx/The Toadz - Street Chase - Loop.mp3");

	camera.Create();

	listDrones.push_back(Drone({512.0f, 470.0f}));

	map.Load("assets/sprites/map01.png", "assets/json/olcCodeJam2024_map.json");

	return true;
}

void Game::OnFixedUpdate()
{	
	player.Update();

	for (auto& drone : listDrones)
		drone.Update();

	camera.Update();

	for (auto& b : player.listBullets)
	{
		for (auto& drone : listDrones)
		{
			//PRINTLN(b.position);
			if (b.position.x > drone.hitbox.position.x && b.position.x < drone.hitbox.position.x + drone.hitbox.size.x &&
				b.position.y > drone.hitbox.position.y && b.position.y < drone.hitbox.position.y + drone.hitbox.size.y)
			{
				drone.destroyed = true;
				b.remove = true;
			}
		}
	}
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

	for (auto& drone : listDrones)
		drone.Draw();
	
	player.Draw();

	listDrones.remove_if([&](const Drone& drone) {return drone.remove; });

	return !GetKey(olc::ESCAPE).bPressed;
}


