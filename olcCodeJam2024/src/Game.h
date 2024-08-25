#pragma once

#include "olcPixelGameEngine.h"
#include "olcPGEX_MiniAudio.h"

#include "Map.h"
#include "Camera.h"

#include "Player.h"
#include "Drone.h"
#include "Bullet.h"
#include "Ladder.h"

#ifdef _DEBUG
#define PRINT(x) std::cout << x
#define PRINTLN(x) std::cout << x << "\n"
#else
#define PRINT(x)
#define PRINTLN(x)
#endif // _DEBUG


enum GameState
{
	TITLE,
	GAME
};


class Game : public olc::PixelGameEngine
{
public:
	Game();
	~Game();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void OnFixedUpdate();

	void Reset();

public:
	GameState gameState;
	bool pause;

	Player player;

	Map map;
	Camera camera;

	double timer;
	double fixedTimeSimulated;
	double countdownToDeath;
	olc::Pixel timerTextColor;

	olc::MiniAudio ma;
	int32_t introMusic;
	int32_t levelMusic;
	int32_t shootSound;
	int32_t enemyShootSound;
	int32_t explosionSound;
	int32_t hurtSound;
	
	int32_t countdownToReset;

	bool victory;
};

inline Game* game;