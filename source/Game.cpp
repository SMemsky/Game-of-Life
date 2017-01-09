#include "Game.h"

#include <iostream>

#include <SFML/OpenGL.hpp>
#include <SFML/Window/Event.hpp>

const std::string Game::applicationName = "Conway's Game of Life";
const unsigned Game::framerate = 60;

Game::Game(std::vector<std::string> const& arguments) :
	columns(64),
	rows(64),
	window(),
	map(columns, rows),
	shallPerformExit(false),
	simulationIsPaused(true),
	gridIsShown(true)
{
	initWindow(640, 640);
	initGL();

	clearMap();
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

void Game::logicUpdate(float deltaTime)
{
	map.update();
}

void Game::clearMap()
{
	Map::CellState numb[3] = {Map::Empty, Map::Set, Map::Set};
	int counterX = 0;
	int counterY = 0;
	for (int x = 0; x < columns; ++x)
	{
		counterY = 0;
		if (counterX == 0)
		{
			for (int y = 0; y < rows; ++y)
			{
				map.set(x, y, Map::Empty);
			}
			counterX++;
		}
		else
		{
			for (int y = 0; y < rows; ++y)
			{
				map.set(x, y, numb[counterY]);
				if (counterY == 2)
				{
					counterY = 0;
				}
				else
				{
					counterY++;
				}
			}

			if (counterX == 2)
			{
				counterX = 0;
			}
			else
			{
				counterX++;
			}
		}
	}
}

void Game::draw(float deltaTime)
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

	if(gridIsShown)
	{
		drawGrid();
	}

	window.display();
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