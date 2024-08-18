#pragma once

#include "olcPixelGameEngine.h"


class Assets
{
public:
	static Assets& get()
	{
		static Assets me;
		return me;
	}

	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

	olc::Sprite* GetSprite(const std::string& name);
	olc::Decal* GetDecal(const std::string& name);

	void LoadSprites();
private:
	Assets();
	~Assets();

	std::map<std::string, olc::Renderable> mapSprites;
};