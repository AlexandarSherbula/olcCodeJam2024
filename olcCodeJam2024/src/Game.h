#pragma once

#include "olcPixelGameEngine.h"
#include "Player.h"

class Game : public olc::PixelGameEngine
{
public:
	Game();
	~Game();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
private:
	Player player;
};

inline Game* game;