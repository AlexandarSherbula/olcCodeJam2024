#include "Game.h"
#include "Assets.h"

Game::Game()
{
	sAppName = "olcCodeJam2024";
	timer = 0.0f;
	fixedTimeSimulated = 0.0f;

	countdownToReset = 180;

	countdownToDeath = 300.0f;

	timerTextColor = olc::WHITE;
}

Game::~Game()
{
	
}

bool Game::OnUserCreate()
{
	Assets::get().LoadSprites();

	gameState = TITLE;

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
	pause = false;
	
	ma.Play(introMusic, true);

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	if (gameState == TITLE)
	{
		std::string text1 = "Welcome to the Warped city!!!";
		std::string text2 = "Crime is all over the place and you happen to be the crook.";
		std::string text3 = "Police is looking after you and you need to RUN to your ship.";
		std::string text4 = "But you have to hurry or else police will bring reinforcements";
		std::string text5 = "and it will be impossible to RUN.";
		std::string text6 = "Best of Luck!!";
		
		std::string text7 =  "CONTROLS";
		std::string text8 =  "A-D - Move";
		std::string text9 =  "W - Climb ladders";
		std::string text10 =  "S - CROUCH";
		std::string text11 = "SPACE - JUMP";
		std::string text12 = "LEFT CLICK - SHOOT";
		std::string text13 = "ESC - PAUSE";
		std::string text14 = "PRESS ENTER TO BEGIN";

		if (GetKey(olc::ENTER).bPressed)
		{
			gameState = GAME;

			ma.Stop(introMusic);
			ma.Play(levelMusic, true);
		}

		Clear(olc::BLACK);

		map.Draw();

		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text1.size() * 16.0f) / 2.0f, 16.0f }, text1, olc::WHITE, { 2.0f, 2.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text2.size() * 8.0f) /  2.0f, 56.0f }, text2, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text3.size() * 8.0f) /  2.0f, 72.0f }, text3, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text4.size() * 8.0f) /  2.0f, 88.0f }, text4, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text5.size() * 8.0f) /  2.0f, 104.0f }, text5, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text6.size() * 8.0f) /  2.0f, 120.0f }, text6, olc::WHITE, { 1.0f, 1.0f });

		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text7.size() * 16.0f) / 2.0f, 184.0f }, text7, olc::WHITE, { 2.0f, 2.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text8.size() * 8.0f) / 2.0f, 216.0f },  text8, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text9.size() * 8.0f) / 2.0f, 232.0f },  text9, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text10.size() * 8.0f) / 2.0f, 248.0f }, text10, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text11.size() * 8.0f) / 2.0f, 264.0f }, text11, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text12.size() * 8.0f) / 2.0f, 280.0f }, text12, olc::WHITE, { 1.0f, 1.0f });
		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text13.size() * 8.0f) / 2.0f, 296.0f }, text13, olc::WHITE, { 1.0f, 1.0f });

		DrawStringDecal({ (ScreenWidth() / 2.0f) - (text14.size() * 16.0f) / 2.0f, ScreenHeight() - 32.0f}, text14, olc::WHITE, {2.0f, 2.0f});
	}
	else
	{
		if (GetKey(olc::ESCAPE).bPressed)
		{
			pause = !pause;
			if (pause)
				ma.Pause(levelMusic);
			else
				ma.Play(levelMusic, true);
		}

		if (!pause)
		{
			timer += fElapsedTime;
			if (!victory)
				countdownToDeath -= fElapsedTime;

			while (fixedTimeSimulated < timer)
			{
				OnFixedUpdate();
				fixedTimeSimulated += 1.0f / 60.0f;
			}

			map.Update();
		}
		

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
				if (countdownToDeath <= 0.0f)
					text = "YOU'VE RUN OUT OF TIME!!!!";
				else
					text = "YOU'VE RUN OUT OF LUCK!!!!";

				DrawStringDecal({ (ScreenWidth() / 2.0f) - (text.size() * 16.0f) / 2.0f, game->ScreenHeight() - 64.0f }, text, olc::WHITE, { 2.0f, 2.0f });
			}
		}


		if (!victory)
			player.Draw();

		if (!player.death)
		{
			FillRectDecal(olc::vf2d(8.0f, 8.0f), olc::vf2d(92.0f, 11.0f), olc::DARK_GREY);
			FillRectDecal(olc::vf2d(9.0f, 9.0f), olc::vf2d(player.health * 18.0f, 9.0f), olc::GREEN);

			int32_t minutes = countdownToDeath / 60;
			int32_t seconds = (int32_t)countdownToDeath % 60;

			std::string strMinutes = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
			std::string strSeconds = (seconds < 10) ? "0" + std::to_string(seconds) : std::to_string(seconds);

			if (countdownToDeath < 60.0f)
				timerTextColor = olc::RED;
			else
				timerTextColor = olc::WHITE;

			DrawStringDecal(olc::vf2d(8.0f, 32.0f), strMinutes + ":" + strSeconds, timerTextColor, { 2.0f, 2.0f });
		}
		else
			ma.Stop(levelMusic);
		
	}

	return true;
}

void Game::OnFixedUpdate()
{
	if (!player.death)
	{
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

		if ((player.position.y + 35.0f > map.size.y) || countdownToDeath <= 0.0f)
		{
			player.death = true;
		}

		if (!victory)
			player.Update();

		for (auto& drone : map.listDrones)
			drone.Update();

		for (auto& turret : map.listTurrets)
			turret.Update();

		camera.Update();
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
	countdownToDeath = 300.0f;

	map.Reset();
	player.Reset();
}