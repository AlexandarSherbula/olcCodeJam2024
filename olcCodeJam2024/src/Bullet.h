#pragma once

#include "Object.h"
#include "olcPixelGameEngine.h"

class Bullet : public AnimatedObject
{
public:
	Bullet();
	Bullet(const olc::vf2d& position, const olc::Pixel& colorTint = olc::WHITE);

	void Travel();
	void HandleAnimation() override;

	void Update() override;
	void Draw() override;
public:
	bool remove;
private:
	olc::Pixel mColorTint;
};