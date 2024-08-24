#pragma once

#include "Object.h"

class Ladder : public Object
{
public:
	Ladder();
	Ladder(const olc::vf2d& position, float height);

	void DrawHitbox();
};