#pragma once

#include "olcPixelGameEngine.h"
#include "../../dependencies/nlohmann/json/json.hpp"

#include "Drone.h"
#include "Turret.h"
#include "Ladder.h"
#include "GoalVehicle.h"

#include <array>

class Map
{
public:
	Map();
	void Load(const std::string& imageFilePath, const std::string& jsonFilePath);
	void Update();
	void Draw();

	void Reset();

	int32_t GetTileID(olc::vi2d unitPos);
private:
	void WrapBackgroundImage(float& spritePosX, float spriteWidth, float scrollSpeed, int lastImageIterator = 0);
public:
	olc::vi2d size;
	std::list<Drone> listDrones;
	std::list<Turret> listTurrets;
	std::vector<Ladder> vecLadders;
	GoalVehicle goalVehicle;

private:
	olc::Renderable mGFX;
	nlohmann::json mJson;
	std::vector<int32_t> mTileIDs;

	int32_t mUnitWidth;
	int32_t mUnitHeight;

	std::array<float, 11> spriteWidths;
};