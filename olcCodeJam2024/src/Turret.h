#pragma once

#include "olcPixelGameEngine.h"
#include "Object.h"
#include "Bullet.h"

class Turret : public AnimatedObject
{
public:
	Turret();
	Turret(const olc::vf2d& position, bool horizontalFlip = false);

	void Update() override;

	void HandleAnimation();

	void Draw() override;
public:
	bool destroyed;
	bool remove;

	std::list<Bullet> listBullets;
	HitBox fireHitbox;

	int32_t countdownToFire;
private:
	bool mHorizontalFlip;
};