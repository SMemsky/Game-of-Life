#pragma once

#include <SFML/Window/Window.hpp>

#include "Map.h"

class Game
{
public:
	Game(std::vector<std::string> const& arguments);

	void run();
private:
	void initWindow(unsigned windowWidth, unsigned windowHeight);
	void initGL();
	void clearMap();

	void eventUpdate(float deltaTime);
	void handleClick(int mouseX, int mouseY);
	void logicUpdate(float deltaTime);
	void draw(float deltaTime);
	void drawGrid();
private:
	static const std::string applicationName;

	static const unsigned framerate;
private:
	const std::size_t columns;
	const std::size_t rows;

	sf::Window window;

	Map map;

	bool exiting;
	bool paused;
	bool grid;
};
