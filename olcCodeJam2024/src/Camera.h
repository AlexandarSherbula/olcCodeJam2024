#pragma once

#include "olcPixelGameEngine.h"

class Camera
{
public:
	Camera();

	void Create();
	void Update();
	void DrawBorders();
public:
	olc::vf2d position;
	olc::vf2d speed;
	
	olc::vf2d offset;
	olc::vf2d focalPoint;
private:
	float mLeftBorder;
	float mRightBorder;
	float mTopBorder;
	float mBottomBorder;
};