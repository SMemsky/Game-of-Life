#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

int main(int argc, char* argv[])
{
	// Construct argument array, but without the first argument
	std::vector<std::string> arguments(argc - 1);
	for (unsigned i = 1; i < argc; ++i)
	{
		arguments[i - 1] = std::string(argv[i]);
	}

	try
	{
		Game game(arguments);
		game.run();
	}
	catch (std::exception & exception)
	{
		std::cout << "Program is terminated after exception is thrown: " <<
			exception.what() << std::endl;
	}

	return 0;
}
