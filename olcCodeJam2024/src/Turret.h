#pragma once

#include "olcPixelGameEngine.h"
#include "Object.h"


class Turret : public Object
{
public:
	Turret();
	Turret(const olc::vf2d& position);
public:
	HitBox fireHitbox;
};