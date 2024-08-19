#include "Map.h"
#include "Game.h"

nlohmann::json Parse(const std::string& jsonFile)
{
	std::ifstream fstream(jsonFile);
	std::string jsonData((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());

	nlohmann::json json = nlohmann::json::parse(jsonData);

	return json;
}

Map::Map()
{
	
}

void Map::Load(const std::string& imageFilePath, const std::string& jsonFilePath)
{
	mGFX.Load(imageFilePath);

	mJson = Parse(jsonFilePath);

	mUnitWidth = mJson["width"];
	mUnitHeight = mJson["height"];

	size = { mUnitWidth * 16, mUnitHeight * 16 };

	mTileIDs.reserve(size.x * size.y);

#ifdef _DEBUG
	if (mJson["infinite"])
	{
		std::cout << "You forgot to turn off infinite" << std::endl;
		__debugbreak();
	}
#endif // DEBUG

	for (int32_t i = 0; i < mUnitWidth * mUnitHeight; i++)
		mTileIDs.push_back(mJson["layers"][0]["data"][i]);
}

int32_t Map::GetTileID(olc::vi2d unitPos)
{
	if (unitPos.x >= 0 && unitPos.x < mUnitWidth &&
		unitPos.y >= 0 && unitPos.y < mUnitHeight)
		return mTileIDs[unitPos.y * mUnitWidth + unitPos.x];

	return -1;
}

void Map::Draw()
{
	game->DrawDecal(-game->camera.offset, mGFX.Decal());
}