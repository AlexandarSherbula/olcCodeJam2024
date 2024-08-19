#include "Assets.h"

void Assets::LoadSprites()
{
	auto load = [&](const std::string& name, const std::string& fileName)
	{
		mapSprites[name].Load(fileName);
	};

	load("idle1", "assets/sprites/player/idle/idle-1.png");
	load("idle2", "assets/sprites/player/idle/idle-2.png");
	load("idle3", "assets/sprites/player/idle/idle-3.png");
	load("idle4", "assets/sprites/player/idle/idle-4.png");

	load("walk1",  "assets/sprites/player/walk/walk-1.png");
	load("walk2",  "assets/sprites/player/walk/walk-2.png");
	load("walk3",  "assets/sprites/player/walk/walk-3.png");
	load("walk4",  "assets/sprites/player/walk/walk-4.png");
	load("walk5",  "assets/sprites/player/walk/walk-5.png");
	load("walk6",  "assets/sprites/player/walk/walk-6.png");
	load("walk7",  "assets/sprites/player/walk/walk-7.png");
	load("walk8",  "assets/sprites/player/walk/walk-8.png");
	load("walk9",  "assets/sprites/player/walk/walk-9.png");
	load("walk10", "assets/sprites/player/walk/walk-10.png");
	load("walk11", "assets/sprites/player/walk/walk-11.png");
	load("walk12", "assets/sprites/player/walk/walk-12.png");
	load("walk13", "assets/sprites/player/walk/walk-13.png");
	load("walk14", "assets/sprites/player/walk/walk-14.png");
	load("walk15", "assets/sprites/player/walk/walk-15.png");
	load("walk16", "assets/sprites/player/walk/walk-16.png");

	load("run1", "assets/sprites/player/run/run-1.png");
	load("run2", "assets/sprites/player/run/run-2.png");
	load("run3", "assets/sprites/player/run/run-3.png");
	load("run4", "assets/sprites/player/run/run-4.png");
	load("run5", "assets/sprites/player/run/run-5.png");
	load("run6", "assets/sprites/player/run/run-6.png");
	load("run7", "assets/sprites/player/run/run-7.png");
	load("run8", "assets/sprites/player/run/run-8.png");
	load("run9", "assets/sprites/player/run/run-9.png");

	load("jump1", "assets/sprites/player/jump/jump-1.png");
	load("jump2", "assets/sprites/player/jump/jump-2.png");
	load("jump3", "assets/sprites/player/jump/jump-3.png");
	load("jump4", "assets/sprites/player/jump/jump-4.png");



	load("buildings-bg",       "assets/sprites/background/buildings-bg.png");
	load("near-buildings-bg",  "assets/sprites/background/near-buildings-bg.png");
	load("skyline-a",          "assets/sprites/background/skyline-a.png");
	load("skyline-b",          "assets/sprites/background/skyline-b.png");

}

Assets::Assets()
{
}

Assets::~Assets()
{
}

olc::Sprite* Assets::GetSprite(const std::string& name)
{
	return mapSprites[name].Sprite();
}

olc::Decal* Assets::GetDecal(const std::string& name)
{
	return mapSprites[name].Decal();
}
