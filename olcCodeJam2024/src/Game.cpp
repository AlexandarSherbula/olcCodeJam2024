#include "Game.h"
#include "Assets.h"

uint32_t increment = 1;

Game::Game()
{
	sAppName = "olcCodeJam2024";
}

Game::~Game()
{
	
}

bool Game::OnUserCreate()
{
	Assets::get().LoadSprites();

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	player.Movement();

	player.HandleAnimation();

	Clear(olc::VERY_DARK_BLUE);

	player.Draw();

	return !GetKey(olc::ESCAPE).bPressed;
}
