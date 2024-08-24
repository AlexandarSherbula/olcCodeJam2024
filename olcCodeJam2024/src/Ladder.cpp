#include "Ladder.h"
#include "Game.h"

Ladder::Ladder()
{
}

Ladder::Ladder(const olc::vf2d& position, float height)
{
	this->position = position;
	hitbox.position = position;
	hitbox.size = { 16.0f, height };
}

void Ladder::DrawHitbox()
{
	game->FillRectDecal(hitbox.position - game->camera.offset, hitbox.size, olc::Pixel(255, 0, 255, 125));
}
