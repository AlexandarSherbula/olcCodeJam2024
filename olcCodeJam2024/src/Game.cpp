#include "Game.h"
#include "Assets.h"

Game::Game()
{
	sAppName = "olcCodeJam2024";
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;

	countdownToReset = 180;
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
	if (!player.death)
	{
		player.Update();

		for (auto& drone : listDrones)
			drone.Update();

		camera.Update();

		for (auto& drone : listDrones)
		{
			for (auto& b : player.listBullets)
			{
				if (CheckCollision(b.hitbox, drone.hitbox))
				{
					drone.destroyed = true;
					b.remove = true;
				}

				if (drone.destroyed)
					break;
			}
			if (drone.destroyed)
				continue;

			if (CheckCollision(player.hitbox, drone.hitbox) && !player.tempInvicible)
			{
				player.ResetSpeed();
				if (!player.hit)
				{
					player.health--;
					player.hit = true;
				}
			}
		}
	}
	else
	{
		//fadeToBlack--;
		//if (fadeToBlack < 0)
		//	fadeToBlack = 0;

		countdownToReset--;
		if (countdownToReset == 0)
		{
			player.death = false;
			game->Reset();
		}
	}
}

void Game::Reset()
{
	countdownToReset = 180;
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;

	map.Reset();
	player.Reset();

	if (!listDrones.empty())
		listDrones.clear();

	listDrones.push_back(Drone({ 512.0f, 470.0f }));
}

bool Game::OnUserUpdate(float fElapsedTime)
{	
	timer += fElapsedTime;

	while (fixedTimeSimulated < timer)
	{
		OnFixedUpdate();
		fixedTimeSimulated += 1.0f / 60.0f;
	}

	Clear(olc::BLACK);

	if (!player.death)
	{
		map.Draw();

		for (auto& drone : listDrones)
			drone.Draw();
	}	
	
	player.Draw();

	listDrones.remove_if([&](const Drone& drone) {return drone.remove; });

	return !GetKey(olc::ESCAPE).bPressed;
}


