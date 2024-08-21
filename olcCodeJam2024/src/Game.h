#pragma once

#include "olcPixelGameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"


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
private:
	olc::MiniAudio ma;
	int song1;
};

inline Game* game;