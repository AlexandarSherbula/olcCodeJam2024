#pragma once

#include "olcPixelGameEngine.h"
#include "Object.h"

class GoalVehicle : public Object
{
public:
	GoalVehicle();
	GoalVehicle(const olc::vf2d& position);

	void Update() override;

	void Draw();
private:
	float mVelocity;

	bool mPlaceVictoryText;
};