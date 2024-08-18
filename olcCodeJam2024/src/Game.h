#pragma once

#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Map.h"

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
	float timer;
	float fixedTimeSimulated;
};

inline Game* game;