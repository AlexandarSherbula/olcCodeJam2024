#include "Game.h"
#include "Assets.h"

Game::Game()
{
	sAppName = "olcCodeJam2024";
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;

	countdownToReset = 180;

	countdownToCops = 300.0f;

	timerTextColor = olc::WHITE;
}

Game::~Game()
{
	
}

bool Game::OnUserCreate()
{
	Assets::get().LoadSprites();

	introMusic      = ma.LoadSound("assets/sfx/music/The Toadz - Sci-Fi Chronicles 19 - Loop.mp3");
	levelMusic      = ma.LoadSound("assets/sfx/music/The Toadz - Street Chase - Loop.mp3");
	shootSound      = ma.LoadSound("assets/sfx/sounds/beam.mp3");
	enemyShootSound = ma.LoadSound("assets/sfx/sounds/enemy-shoot.mp3");
	explosionSound  = ma.LoadSound("assets/sfx/sounds/explosion.mp3");
	hurtSound       = ma.LoadSound("assets/sfx/sounds/hurt.mp3");

	ma.SetVolume(levelMusic, 1.0f);
	ma.SetVolume(hurtSound, 2.0f);

	camera.Create();

	map.Load("assets/sprites/map01.png", "assets/json/olcCodeJam2024_map.json");

	victory = false;
	
	ma.Play(levelMusic, true);

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	//if (GetKey(olc::P).bPressed)
	//{
	//	ma.Stop(music2);
	//	ma.Play(music, true);
	//}

	timer += fElapsedTime;
	if (!victory)
		countdownToCops -= fElapsedTime;

	while (fixedTimeSimulated < timer)
	{
		OnFixedUpdate();
		fixedTimeSimulated += 1.0f / 60.0f;
	}

	map.Update();

	Clear(olc::BLACK);

	if (!player.death)
	{
		map.Draw();
	}
	else
	{
		if (countdownToReset <= 120)
		{
			std::string text = " ";
			if (countdownToCops <= 0.0f)
				text = "YOU'VE RUN OUT OF TIME!!!!";
			else
				text = "YOU'VE RUN OUT OF LUCK!!!!";

			DrawStringDecal({ (ScreenWidth() / 2.0f) - (text.size() * 16.0f) / 2.0f, game->ScreenHeight() - 64.0f}, text, olc::WHITE, {2.0f, 2.0f});
		}
	}
	
	if (!victory)
		player.Draw();

	if (!player.death)
	{
		FillRectDecal(olc::vf2d(8.0f, 8.0f), olc::vf2d(92.0f, 11.0f), olc::DARK_GREY);
		FillRectDecal(olc::vf2d(9.0f, 9.0f), olc::vf2d(player.health * 18.0f, 9.0f), olc::GREEN);

		int32_t minutes = countdownToCops / 60;
		int32_t seconds = (int32_t)countdownToCops % 60;

		std::string strMinutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
		std::string strSeconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

		if (countdownToCops < 60.0f)
			timerTextColor = olc::RED;
		else
			timerTextColor = olc::WHITE;

		DrawStringDecal(olc::vf2d(8.0f, 32.0f), strMinutes + ":" + strSeconds, timerTextColor, { 2.0f, 2.0f });
	}
	else
		ma.Stop(levelMusic);

#if _DEBUG
	return !GetKey(olc::ESCAPE).bPressed;
#else
	return true;
#endif // _DEBUG
}

void Game::OnFixedUpdate()
{
	if (!player.death)
	{
		if (!victory)
			player.Update();

		for (auto& drone : map.listDrones)
			drone.Update();

		for (auto& turret : map.listTurrets)
			turret.Update();

		camera.Update();

		for (auto& drone : map.listDrones)
		{
			for (auto& b : player.listBullets)
			{
				if (CheckCollision(b.hitbox, drone.hitbox))
				{
					drone.destroyed = true;
					b.remove = true;
					ma.Play(explosionSound);
				}

				if (drone.destroyed)
					break;
			}
			if (drone.destroyed)
				continue;

			if (CheckCollision(player.hitbox, drone.hitbox) && !player.tempInvicible)
			{
				player.Hurt();
			}
		}

		for (auto& turret : map.listTurrets)
		{
			for (auto& b : player.listBullets)
			{
				if (CheckCollision(b.hitbox, turret.hitbox))
				{
					turret.destroyed = true;
					b.remove = true;
					ma.Play(explosionSound);
				}

				if (turret.destroyed)
					break;
			}

			for (auto& b : turret.listBullets)
			{
				if (CheckCollision(b.hitbox, player.hitbox) && !player.tempInvicible)
				{
					player.Hurt();
					b.remove = true;
				}
			}

			if (turret.destroyed)
				continue;

			if (CheckCollision(player.hitbox, turret.hitbox) && !player.tempInvicible)
			{
				player.Hurt();
			}
		}

		for (auto& ladder : map.vecLadders)
		{
			if (CheckCollision(player.hitbox, ladder.hitbox))
			{
				if (GetKey(olc::W).bHeld && !player.crouch)
				{
					if (!player.isClimbing)
					{
						player.isClimbing = true;
						player.SetAnimationState(AnimationState::CLIMB);
					}
					player.Climb(ladder.hitbox.position);
				}
				else
					player.climbMove = false;

				if (player.position.y + 10.0f < ladder.position.y && player.isClimbing)
				{
					player.isClimbing = false;
					player.SetAnimationState(AnimationState::IDLE);
				}
				
			}
		}

		if ((player.position.y + 35.0f > map.size.y) || countdownToCops <= 0.0f)
		{
			player.death = true;
		}
	}
	else if (player.death)
	{
		countdownToReset--;
		if (countdownToReset == 0)
		{
			player.death = false;
			Reset();
		}
	}

	map.goalVehicle.Update();
}

void Game::Reset()
{
	ma.Play(levelMusic, true);
	countdownToReset = 180;
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;
	countdownToCops = 300.0f;

	map.Reset();
	player.Reset();
}