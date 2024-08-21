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

	spriteWidths[0] = 0.0f;
	spriteWidths[1] = Assets::get().GetDecal("skyline-city")->sprite->width * 2.0f;
	spriteWidths[2] = Assets::get().GetDecal("skyline-city")->sprite->width * 4.0f;
	spriteWidths[3] = Assets::get().GetDecal("skyline-city")->sprite->width * 6.0f;

	spriteWidths[4] = 0.0f;
	spriteWidths[5] = Assets::get().GetDecal("buildings-bg")->sprite->width * 2.0f;
	spriteWidths[6] = Assets::get().GetDecal("buildings-bg")->sprite->width * 4.0f;
	spriteWidths[7] = Assets::get().GetDecal("buildings-bg")->sprite->width * 6.0f;

	spriteWidths[8] = 0.0f;
	spriteWidths[9] = Assets::get().GetDecal("near-buildings-bg")->sprite->width;
	spriteWidths[10] = Assets::get().GetDecal("near-buildings-bg")->sprite->width * 2.0f;
}

int32_t Map::GetTileID(olc::vi2d unitPos)
{
	if (unitPos.x >= 0 && unitPos.x < mUnitWidth &&
		unitPos.y >= 0 && unitPos.y < mUnitHeight)
		return mTileIDs[unitPos.y * mUnitWidth + unitPos.x];

	return -1;
}

void Map::WrapBackgroundImage(float& spritePosX, float spriteWidth, float scrollSpeed, int lastImageIterator)
{
	if (game->player.direction == Direction::RIGHT)
	{
		if (spritePosX + scrollSpeed <= -spriteWidth)
		{
			spritePosX = spriteWidth * lastImageIterator;
		}
	}
	else
	{
		if (spritePosX + scrollSpeed >= spriteWidth * lastImageIterator)
		{
			spritePosX = -spriteWidth;
		}
	}
	
}

void Map::Draw()
{
	olc::vf2d scale = {2.0f, 2.0f};

	game->DrawDecal(olc::vf2d(0.0f, 0.0f), Assets::get().GetDecal("skyline"), scale);

	float spriteWidth = Assets::get().GetDecal("skyline-city")->sprite->width * scale.x;
	float spriteHeight = Assets::get().GetDecal("skyline")->sprite->height * scale.y;

	WrapBackgroundImage(spriteWidths[0], spriteWidth, -game->camera.offset.x / 48.0f, 3);
	WrapBackgroundImage(spriteWidths[1], spriteWidth, -game->camera.offset.x / 48.0f, 3);
	WrapBackgroundImage(spriteWidths[2], spriteWidth, -game->camera.offset.x / 48.0f, 3);
	WrapBackgroundImage(spriteWidths[3], spriteWidth, -game->camera.offset.x / 48.0f, 3);
	
	game->DrawDecal(olc::vf2d(spriteWidths[0] - game->camera.offset.x / 48.0f, spriteHeight), Assets::get().GetDecal("skyline-city"), scale);
	game->DrawDecal(olc::vf2d(spriteWidths[1] - game->camera.offset.x / 48.0f, spriteHeight), Assets::get().GetDecal("skyline-city"), scale);
	game->DrawDecal(olc::vf2d(spriteWidths[2] - game->camera.offset.x / 48.0f, spriteHeight), Assets::get().GetDecal("skyline-city"), scale);
	game->DrawDecal(olc::vf2d(spriteWidths[3] - game->camera.offset.x / 48.0f, spriteHeight), Assets::get().GetDecal("skyline-city"), scale);
	
	spriteWidth = Assets::get().GetDecal("buildings-bg")->sprite->width * scale.x;

	WrapBackgroundImage(spriteWidths[4], spriteWidth, -game->camera.offset.x / 24.0f, 3);
	WrapBackgroundImage(spriteWidths[5], spriteWidth, -game->camera.offset.x / 24.0f, 3);
	WrapBackgroundImage(spriteWidths[6], spriteWidth, -game->camera.offset.x / 24.0f, 3);
	WrapBackgroundImage(spriteWidths[7], spriteWidth, -game->camera.offset.x / 24.0f, 3);
	
	game->DrawDecal(olc::vf2d(spriteWidths[4] - game->camera.offset.x / 24.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);
	game->DrawDecal(olc::vf2d(spriteWidths[5] - game->camera.offset.x / 24.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);
	game->DrawDecal(olc::vf2d(spriteWidths[6] - game->camera.offset.x / 24.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);
	game->DrawDecal(olc::vf2d(spriteWidths[7] - game->camera.offset.x / 24.0f, 120.0f), Assets::get().GetDecal("buildings-bg"), scale);
	
	spriteWidth = Assets::get().GetDecal("near-buildings-bg")->sprite->width;

	WrapBackgroundImage(spriteWidths[8],  spriteWidth,  -game->camera.offset.x / 12.0f, 2);
	WrapBackgroundImage(spriteWidths[9],  spriteWidth,  -game->camera.offset.x / 12.0f, 2);
	WrapBackgroundImage(spriteWidths[10], spriteWidth,  -game->camera.offset.x / 12.0f, 2);
	
	game->DrawDecal(olc::vf2d(spriteWidths[8]  - game->camera.offset.x / 12.0f, 180.0f - game->camera.offset.y / 24.0f), Assets::get().GetDecal("near-buildings-bg"));
	game->DrawDecal(olc::vf2d(spriteWidths[9]  - game->camera.offset.x / 12.0f, 180.0f - game->camera.offset.y / 24.0f), Assets::get().GetDecal("near-buildings-bg"));
	game->DrawDecal(olc::vf2d(spriteWidths[10] - game->camera.offset.x / 12.0f, 180.0f - game->camera.offset.y / 24.0f), Assets::get().GetDecal("near-buildings-bg"));
	
	game->DrawDecal(-game->camera.offset, mGFX.Decal());
}