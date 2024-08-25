#pragma once


#include "olcPixelGameEngine.h"
#include "Object.h"


class Chaser : public Object
{
public:
	Chaser();
	Chaser(const olc::vf2d& position, bool isFlipped);

	void Update() override;

	void Draw() override;
public:
	HitBox trigger;
	bool drive;
private:
	bool mHorizontalFlip;
};