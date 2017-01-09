#include "Game.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Window/Event.hpp>

const std::string Game::applicationName = "Conway's Game of Life";
const unsigned Game::framerate = 600;

Game::Game(std::vector<std::string> const& arguments) :
	mapSizeX(32),
	mapSizeY(32),
	window(),
	map(mapSizeX, mapSizeY),
	exiting(false),
	paused(true),
	grid(true)
{
	initWindow();
	initGL();
	cleanMap();
}

void Game::run()
{
	sf::Clock deltaTimer;
	while(!exiting)
	{
		sf::Time deltaTime = deltaTimer.restart();
		eventUpdate(deltaTime.asSeconds());
		if (!paused)
		{
			logicUpdate(deltaTime.asSeconds());
		}
		draw(deltaTime.asSeconds());
	}

	window.close();
}

void Game::initWindow()
{
	window.create(sf::VideoMode(1000, 1000), Game::applicationName);
	window.setFramerateLimit(framerate);
}

void Game::initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.getSize().x, window.getSize().y, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::cleanMap()
{
	Map::CellState numb[3] = {Map::Empty, Map::Set, Map::Set};
	int counterX = 0;
	int counterY = 0;
	for (int x = 0; x < mapSizeX; ++x)
	{
		counterY = 0;
		if (counterX == 0)
		{
			for (int y = 0; y < mapSizeY; ++y)
			{
				map.set(x, y, Map::Empty);
			}
			counterX++;
		}
		else
		{
			for (int y = 0; y < mapSizeY; ++y)
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

void Game::eventUpdate(float deltaTime)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			exiting = true;
		}
		else if (event.type == sf::Event::Resized)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, event.size.width, event.size.height, 0, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glViewport(0, 0, event.size.width, event.size.height);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				paused = !paused;
			}
			else if (event.key.code == sf::Keyboard::G)
			{
				grid = !grid;
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				exiting = true;
			}
			else if (event.key.code == sf::Keyboard::R)
			{
				cleanMap();
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				handleClick(event.mouseButton.x, event.mouseButton.y);
			}	
		}
	}
}

void Game::handleClick(int x, int y)
{
	int tmpX = static_cast<int>(static_cast<float>(x) / (static_cast<float>(window.getSize().x / static_cast<float>(mapSizeX))));
	int tmpY = static_cast<int>(static_cast<float>(y) / (static_cast<float>(window.getSize().y / static_cast<float>(mapSizeY))));
	
	map.set(tmpX, tmpY,
		(map.get(tmpX, tmpY) == Map::Set) ? Map::Empty : Map::Set);
}

void Game::logicUpdate(float deltaTime)
{
	map.update();
}

void Game::draw(float deltaTime)
{
	const float dotSizeX = static_cast<float>(window.getSize().x) / static_cast<float>(mapSizeX);
	const float dotSizeY = static_cast<float>(window.getSize().y) / static_cast<float>(mapSizeY);

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int x = 0; x < mapSizeX; ++x)
	{
		for (int y =0; y < mapSizeY; ++y)
		{
			if (map.get(x, y))
			{
				glVertex2f(x * dotSizeX, y * dotSizeY);
				glVertex2f(x * dotSizeX + dotSizeX, y * dotSizeY);
				glVertex2f(x * dotSizeX + dotSizeX, y * dotSizeY + dotSizeY);
				glVertex2f(x * dotSizeX, y * dotSizeY + dotSizeY);
			}
		}
	}
	glEnd();

	if(grid)
	{
		drawGrid();
	}

	window.display();
}

void Game::drawGrid()
{
	const float dotSizeX = static_cast<float>(window.getSize().x) / static_cast<float>(mapSizeX);
	const float dotSizeY = static_cast<float>(window.getSize().y) / static_cast<float>(mapSizeY);

	glBegin(GL_LINES);
	glColor3f(0.35f, 0.32f, 0.32f);
	for (int x = 0; x < mapSizeX; ++x)
	{
		glVertex2f(x * dotSizeX, 0);
		glVertex2f(x * dotSizeX, mapSizeY * dotSizeY);
	}
	for (int y = 0; y < mapSizeY; ++y)
	{
		glVertex2f(0, y * dotSizeY);
		glVertex2f(mapSizeX * dotSizeX, y * dotSizeY); 
	}
	glEnd();
}