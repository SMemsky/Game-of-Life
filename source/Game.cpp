#include "Game.h"

#include <cassert>

#include <SFML/OpenGL.hpp>
#include <SFML/Window/Event.hpp>

const std::string Game::applicationName = "Conway's Game of Life";
const unsigned Game::framerate = 60;

Game::Game(std::vector<std::string> const& arguments) :
	columns(64),
	rows(64),
	window(),
	map(columns, rows),
	temporaryMap(columns, rows),
	shallPerformExit(false),
	simulationIsPaused(true),
	gridIsShown(true)
{
	initWindow(640, 640);
	initGL();

	clearMap(StableSquares);
}

void Game::run()
{
	sf::Clock deltaTimer;
	while(!shallPerformExit)
	{
		sf::Time deltaTime = deltaTimer.restart();
		eventUpdate(deltaTime.asSeconds());
		if (!simulationIsPaused)
		{
			logicUpdate(deltaTime.asSeconds());
		}
		draw(deltaTime.asSeconds());
	}

	window.close();
}

void Game::initWindow(unsigned windowWidth, unsigned windowHeight)
{
	window.create(sf::VideoMode(windowWidth, windowHeight),
		Game::applicationName);
	window.setFramerateLimit(framerate);
}

void Game::initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	setViewport(window.getSize().x, window.getSize().y);
}

void Game::setViewport(unsigned width, unsigned height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, width, height, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, width, height);
}

void Game::handleKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::P:
		{
			simulationIsPaused = !simulationIsPaused;

			break;
		}
		case sf::Keyboard::G:
		{
			gridIsShown = !gridIsShown;

			break;
		}
		case sf::Keyboard::Q:
		{
			shallPerformExit = true;

			break;
		}
		case sf::Keyboard::R:
		{
			clearMap();

			break;
		}
		default:
		{
			break;
		}
	}
}

void Game::handleClick(int mouseX, int mouseY)
{
	if (mouseX < 0 ||
		mouseY < 0)
	{
		return;
	}

	const float columnWidth = static_cast<float>(window.getSize().x) / columns;
	const float rowHeight = static_cast<float>(window.getSize().y) / rows;

	const unsigned cellX = mouseX / columnWidth;
	const unsigned cellY = mouseY / rowHeight;
	
	map.set(cellX, cellY,
		(map.get(cellX, cellY) == Map::Set) ? Map::Empty : Map::Set);
}

void Game::eventUpdate(float deltaTime)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				shallPerformExit = true;

				break;
			}
			case sf::Event::Resized:
			{
				setViewport(event.size.width, event.size.height);

				break;
			}
			case sf::Event::KeyPressed:
			{
				handleKeyPress(event.key.code);

				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					handleClick(event.mouseButton.x, event.mouseButton.y);
				}

				break;
			}
			default:
			{
				break;
			}
		}
	}
}

unsigned Game::countNeighbors(int x, int y) const
{
	unsigned count = 0;

	if (map.get(x, y + 1)) { ++count; } //Top
	if (map.get(x, y - 1)) { ++count; } //Down
	if (map.get(x + 1, y)) { ++count; } //Right
	if (map.get(x - 1, y)) { ++count; } //Left

	if (map.get(x + 1, y + 1)) { ++count; } //Top right
	if (map.get(x - 1, y + 1)) { ++count; } //Top left
	if (map.get(x + 1, y - 1)) { ++count; } //Down right
	if (map.get(x - 1, y - 1)) { ++count; } //Down left

	return count;
}

void Game::logicUpdate(float deltaTime)
{
	for (unsigned column = 0; column < columns; ++column)
	{
		for (unsigned row = 0; row < rows; ++row)
		{
			unsigned neighbors = countNeighbors(column, row);

			if (map.get(column, row) == Map::Set)
			{
				temporaryMap.set(column, row,
					(neighbors == 2 || neighbors == 3) ? Map::Set : Map::Empty);
			}
			else
			{
				temporaryMap.set(column, row, (neighbors == 3) ? Map::Set : Map::Empty);
			}
		}
	}

	map.swap(temporaryMap);
}

void Game::setEmptyPreset()
{
	for (unsigned column = 0; column < columns; ++column)
	{
		for (unsigned row = 0; row < rows; ++row)
		{
			map.set(column, row, Map::Empty);
		}
	}
}

void Game::setSquaresPreset()
{
	for (unsigned column = 0; column < columns; ++column)
	{
		for (unsigned row = 0; row < rows; ++row)
		{
			if (column % 3 == 0 ||
				row % 3 == 0)
			{
				map.set(column, row, Map::Empty);
			}
			else
			{
				map.set(column, row, Map::Set);
			}
		}
	}
}

void Game::clearMap(MapPreset preset)
{
	switch (preset)
	{
		case Empty:
		{
			setEmptyPreset();

			break;
		}
		case StableSquares:
		{
			setSquaresPreset();

			break;
		}
		default:
		{
			assert(false);

			break;
		}
	}
}

void Game::drawCells()
{
	const float columnWidth = static_cast<float>(window.getSize().x) / columns;
	const float rowHeight = static_cast<float>(window.getSize().y) / rows;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		for (unsigned column = 0; column < columns; ++column)
		{
			for (unsigned row = 0; row < rows; ++row)
			{
				if (map.get(column, row) == Map::Set)
				{
					glVertex2f(column * columnWidth, row * rowHeight);
					glVertex2f(column * columnWidth + columnWidth,
						row * rowHeight);
					glVertex2f(column * columnWidth + columnWidth,
						row * rowHeight + rowHeight);
					glVertex2f(column * columnWidth,
						row * rowHeight + rowHeight);
				}
			}
		}
	}
	glEnd();
}

void Game::drawGrid()
{
	const float columnWidth = static_cast<float>(window.getSize().x) / columns;
	const float rowHeight = static_cast<float>(window.getSize().y) / rows;

	glBegin(GL_LINES);
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		for (unsigned column = 0; column < columns; ++column)
		{
			glVertex2f(column * columnWidth, 0);
			glVertex2f(column * columnWidth, rows * rowHeight);
		}
		for (unsigned row = 0; row < rows; ++row)
		{
			glVertex2f(0, row * rowHeight);
			glVertex2f(columns * columnWidth, row * rowHeight); 
		}
	}
	glEnd();
}

void Game::draw(float deltaTime)
{
	drawCells();

	if(gridIsShown)
	{
		drawGrid();
	}

	window.display();
}
