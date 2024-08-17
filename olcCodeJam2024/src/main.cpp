#include "Game.h"

int main()
{
	game = new Game();
	if (game->Construct(640, 360, 2, 2, false, true))
		game->Start();
	delete game;
	return 0;
}