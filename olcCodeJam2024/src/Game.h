#pragma once

#include "olcPixelGameEngine.h"
#include "Map.h"
#include "Camera.h"

#include "Player.h"
#include "Bullet.h"

#include "olcPGEX_MiniAudio.h"

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
	Bullet bullet;

	olc::MiniAudio ma;
	int32_t song1;
};

inline Game* game;