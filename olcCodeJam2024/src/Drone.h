#pragma once

#include "Object.h"
#include "olcPixelGameEngine.h"


class Drone : public AnimatedObject
{
public:
	Drone();
	Drone(const olc::vf2d& position);

	void Update() override;
	void HandleAnimation() override;

	void Draw() override;
public:
	bool destroyed;
	bool remove;
private:
	float mSpeed;
	bool mRotateAnimation;
};