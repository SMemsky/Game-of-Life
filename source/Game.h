#pragma once

#include <SFML/Window/Window.hpp>

#include "Map.h"

class Game
{
public:
	Game(std::vector<std::string> const& arguments);

	void run();
private:
	void initWindow();
	void initGL();
	void cleanMap();

	void eventUpdate(float deltaTime);
	void handleClick(int x, int y);
	void logicUpdate(float deltaTime);
	void draw(float deltaTime);
	void drawGrid();
private:
	static const std::string applicationName;

	static const unsigned framerate;
private:
	const std::size_t mapSizeX;
	const std::size_t mapSizeY;

	sf::Window window;

	Map map;

	bool exiting;
	bool paused;
	bool grid;
};
