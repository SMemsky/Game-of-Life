#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

#include "Map.h"

class Game
{
	enum MapPreset
	{
		Empty = 1,
		StableSquares = 2
	};
public:
	Game(std::vector<std::string> const& arguments);

	void run();
private:
	// Initialization
	void initWindow(unsigned windowWidth, unsigned windowHeight);
	void initGL();

	// Event handling
	void setViewport(unsigned width, unsigned height);
	void handleKeyPress(sf::Keyboard::Key key);
	void handleClick(int mouseX, int mouseY);
	void eventUpdate(float deltaTime);

	// Logic
	unsigned countNeighbors(int x, int y) const;
	void logicUpdate(float deltaTime);
	void setEmptyPreset();
	void setSquaresPreset();
	void clearMap(MapPreset preset = Empty);

	// Rendering
	void drawCells();
	void drawGrid();
	void draw(float deltaTime);
private:
	static const std::string applicationName;

	static const unsigned framerate;
private:
	const std::size_t columns;
	const std::size_t rows;

	sf::Window window;

	Map map;
	Map temporaryMap;

	bool shallPerformExit;
	bool simulationIsPaused;
	bool gridIsShown;
};
