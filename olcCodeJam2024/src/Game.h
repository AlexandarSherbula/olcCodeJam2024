#pragma once

#include "olcPixelGameEngine.h"
#include "Map.h"
#include "Camera.h"

#include "Player.h"
#include "Bullet.h"

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

public:
	Player player;
	Map map;
	Camera camera;

	double timer;
	double fixedTimeSimulated;
	olc::vf2d shotPos;
	float shotSpeed;

	olc::MiniAudio ma;
	int32_t song1;
};

inline Game* game;