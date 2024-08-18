#pragma once

#include "olcPixelGameEngine.h"

#include "../assets/nlohmann/json/json.hpp"

class Map
{
public:
	Map();
	void Load(const std::string& imageFilePath, const std::string& jsonFilePath);
	void Draw();

	int32_t GetTileID(olc::vi2d unitPos);
public:
	olc::vi2d size;
private:
	olc::Renderable mGFX;
	nlohmann::json mJson;
	std::vector<int32_t> mTileIDs;

	int32_t mUnitWidth;
	int32_t mUnitHeight;
};