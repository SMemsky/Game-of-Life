#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>

#include "Map.h"

class Game
{
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
	void logicUpdate(float deltaTime);
	void clearMap();

	// Rendering
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

	bool shallPerformExit;
	bool simulationIsPaused;
	bool gridIsShown;
};
