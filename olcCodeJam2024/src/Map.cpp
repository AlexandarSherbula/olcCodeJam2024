#include "Map.h"
#include "Game.h"
#include "Assets.h"

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
	olc::vf2d scale = {2.0f, 2.0f};

	game->DrawDecal(olc::vf2d(0.0f - game->camera.offset.x / 16.0f, -100.0f), Assets::get().GetDecal("skyline-a"), scale);

	float spriteWidth = Assets::get().GetDecal("skyline-b")->sprite->width * scale.x;

	game->DrawDecal(olc::vf2d(spriteWidth - game->camera.offset.x / 16.0f, -100.0f), Assets::get().GetDecal("skyline-b"), scale);
	game->DrawDecal(olc::vf2d(spriteWidth * 2.0f - game->camera.offset.x / 16.0f, -100.0f), Assets::get().GetDecal("skyline-a"), scale);

	spriteWidth = Assets::get().GetDecal("buildings-bg")->sprite->width * scale.x;

	game->DrawDecal(olc::vf2d(0.0f - game->camera.offset.x / 8.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);
	game->DrawDecal(olc::vf2d(spriteWidth - game->camera.offset.x / 8.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);
	game->DrawDecal(olc::vf2d(spriteWidth * 2.0f - game->camera.offset.x / 8.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);

	spriteWidth = Assets::get().GetDecal("near-buildings-bg")->sprite->width;

	game->DrawDecal(olc::vf2d(0.0f - game->camera.offset.x / 4.0f, 180.0f - game->camera.offset.y / 24.0f), Assets::get().GetDecal("near-buildings-bg"));
	game->DrawDecal(olc::vf2d(spriteWidth - game->camera.offset.x / 4.0f, 180.0f - game->camera.offset.y / 24.0f), Assets::get().GetDecal("near-buildings-bg"));

	game->DrawDecal(-game->camera.offset, mGFX.Decal());
}