#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game;
	if (argc < 4)
	{
		game = new Game(75, 75, 10);
	}
	else
	{
		game = new Game(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}

	game->Start();
	return 0;
}