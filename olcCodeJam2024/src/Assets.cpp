#include "Assets.h"

void Assets::LoadSprites()
{
	auto load = [&](const std::string& name, const std::string& fileName)
	{
		mapSprites[name].Load(fileName);
	};

	load("idle1",               "assets/sprites/player/idle/idle-1.png");
	load("idle2",               "assets/sprites/player/idle/idle-2.png");
	load("idle3",               "assets/sprites/player/idle/idle-3.png");
	load("idle4",               "assets/sprites/player/idle/idle-4.png");

	load("walk1",               "assets/sprites/player/walk/walk-1.png");
	load("walk2",               "assets/sprites/player/walk/walk-2.png");
	load("walk3",               "assets/sprites/player/walk/walk-3.png");
	load("walk4",               "assets/sprites/player/walk/walk-4.png");
	load("walk5",               "assets/sprites/player/walk/walk-5.png");
	load("walk6",               "assets/sprites/player/walk/walk-6.png");
	load("walk7",               "assets/sprites/player/walk/walk-7.png");
	load("walk8",               "assets/sprites/player/walk/walk-8.png");
	load("walk9",               "assets/sprites/player/walk/walk-9.png");
	load("walk10",              "assets/sprites/player/walk/walk-10.png");
	load("walk11",              "assets/sprites/player/walk/walk-11.png");
	load("walk12",              "assets/sprites/player/walk/walk-12.png");
	load("walk13",              "assets/sprites/player/walk/walk-13.png");
	load("walk14",              "assets/sprites/player/walk/walk-14.png");
	load("walk15",              "assets/sprites/player/walk/walk-15.png");
	load("walk16",              "assets/sprites/player/walk/walk-16.png");

	load("walk-shoot1",         "assets/sprites/player/walk-shoot/walk-shoot-1.png");
	load("walk-shoot2",         "assets/sprites/player/walk-shoot/walk-shoot-2.png");
	load("walk-shoot3",         "assets/sprites/player/walk-shoot/walk-shoot-3.png");
	load("walk-shoot4",         "assets/sprites/player/walk-shoot/walk-shoot-4.png");
	load("walk-shoot5",         "assets/sprites/player/walk-shoot/walk-shoot-5.png");
	load("walk-shoot6",         "assets/sprites/player/walk-shoot/walk-shoot-6.png");
	load("walk-shoot7",         "assets/sprites/player/walk-shoot/walk-shoot-7.png");
	load("walk-shoot8",         "assets/sprites/player/walk-shoot/walk-shoot-8.png");
	load("walk-shoot9",         "assets/sprites/player/walk-shoot/walk-shoot-9.png");
	load("walk-shoot10",        "assets/sprites/player/walk-shoot/walk-shoot-10.png");
	load("walk-shoot11",        "assets/sprites/player/walk-shoot/walk-shoot-11.png");
	load("walk-shoot12",        "assets/sprites/player/walk-shoot/walk-shoot-12.png");
	load("walk-shoot13",        "assets/sprites/player/walk-shoot/walk-shoot-13.png");
	load("walk-shoot14",        "assets/sprites/player/walk-shoot/walk-shoot-14.png");
	load("walk-shoot15",        "assets/sprites/player/walk-shoot/walk-shoot-15.png");
	load("walk-shoot16",        "assets/sprites/player/walk-shoot/walk-shoot-16.png");

	load("run1",                "assets/sprites/player/run/run-1.png");
	load("run2",                "assets/sprites/player/run/run-2.png");
	load("run3",                "assets/sprites/player/run/run-3.png");
	load("run4",                "assets/sprites/player/run/run-4.png");
	load("run5",                "assets/sprites/player/run/run-5.png");
	load("run6",                "assets/sprites/player/run/run-6.png");
	load("run7",                "assets/sprites/player/run/run-7.png");
	load("run8",                "assets/sprites/player/run/run-8.png");
	load("run9",                "assets/sprites/player/run/run-9.png");

	load("jump1",               "assets/sprites/player/jump/jump-1.png");
	load("jump2",               "assets/sprites/player/jump/jump-2.png");
	load("jump3",               "assets/sprites/player/jump/jump-3.png");
	load("jump4",               "assets/sprites/player/jump/jump-4.png");

	load("climb1",               "assets/sprites/player/climb/climb-1.png");
	load("climb2",               "assets/sprites/player/climb/climb-2.png");
	load("climb3",               "assets/sprites/player/climb/climb-3.png");
	load("climb4",               "assets/sprites/player/climb/climb-4.png");
	load("climb5",               "assets/sprites/player/climb/climb-5.png");
	load("climb6",               "assets/sprites/player/climb/climb-6.png");

	load("shoot",               "assets/sprites/player/shoot/shoot.png");

	load("run-shoot1",          "assets/sprites/player/run-shoot/run-shoot-1.png");
	load("run-shoot2",          "assets/sprites/player/run-shoot/run-shoot-2.png");
	load("run-shoot3",          "assets/sprites/player/run-shoot/run-shoot-3.png");
	load("run-shoot4",          "assets/sprites/player/run-shoot/run-shoot-4.png");
	load("run-shoot5",          "assets/sprites/player/run-shoot/run-shoot-5.png");
	load("run-shoot6",          "assets/sprites/player/run-shoot/run-shoot-6.png");
	load("run-shoot7",          "assets/sprites/player/run-shoot/run-shoot-7.png");
	load("run-shoot8",          "assets/sprites/player/run-shoot/run-shoot-8.png");

	load("hurt",                "assets/sprites/player/hurt/hurt.png");

	load("drone1",              "assets/sprites/misc/drone/drone-1.png");
	load("drone2",              "assets/sprites/misc/drone/drone-2.png");
	load("drone3",              "assets/sprites/misc/drone/drone-3.png");
	load("drone4",              "assets/sprites/misc/drone/drone-4.png");

	load("enemy-explosion1",    "assets/sprites/misc/enemy-explosion/enemy-explosion-1.png");
	load("enemy-explosion2",    "assets/sprites/misc/enemy-explosion/enemy-explosion-2.png");
	load("enemy-explosion3",    "assets/sprites/misc/enemy-explosion/enemy-explosion-3.png");
	load("enemy-explosion4",    "assets/sprites/misc/enemy-explosion/enemy-explosion-4.png");
	load("enemy-explosion5",    "assets/sprites/misc/enemy-explosion/enemy-explosion-5.png");
	load("enemy-explosion6",    "assets/sprites/misc/enemy-explosion/enemy-explosion-6.png");

	load("shot1",               "assets/sprites/misc/shot/shot-1.png");
	load("shot2",               "assets/sprites/misc/shot/shot-2.png");
	load("shot3",               "assets/sprites/misc/shot/shot-3.png");

	load("buildings-bg",        "assets/sprites/background/buildings-bg.png");
	load("near-buildings-bg",   "assets/sprites/background/near-buildings-bg.png");
	load("skyline-a",           "assets/sprites/background/skyline-a.png");
	load("skyline-b",           "assets/sprites/background/skyline-b.png");
	load("skyline",             "assets/sprites/background/skyline.png");
	load("skyline-city",        "assets/sprites/background/skyline-city.png");
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
