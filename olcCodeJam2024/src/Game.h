#pragma once

#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"

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
};

inline Game* game;