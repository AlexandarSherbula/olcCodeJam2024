#pragma once

#include "olcPixelGameEngine.h"
#include "Map.h"
#include "Camera.h"

#include "Player.h"
#include "Drone.h"
#include "Bullet.h"
#include "Ladder.h"

#include "olcPGEX_MiniAudio.h"

#ifdef _DEBUG
#define PRINT(x) std::cout << x
#define PRINTLN(x) std::cout << x << "\n"
#else
#define PRINT(x)
#define PRINTLN(x)
#endif // _DEBUG


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
	Player player;

	Map map;
	Camera camera;

	double timer;
	double fixedTimeSimulated;
	double countdownToCops;
	olc::Pixel timerTextColor;

	olc::MiniAudio ma;
	int32_t song1;
	
	int32_t countdownToReset;

	bool victory;
};

inline Game* game;