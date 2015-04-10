#include <SFML/OpenGL.hpp>
#include <iostream>
using std::cout;
using std::endl;

#include "Game.h"

Game::Game() :
	window(),
	exiting(false),
	paused(true),
	grid(true),
	mapSizeX(25),
	mapSizeY(25)

{
	map = new bool*[mapSizeX];

	for (size_t i = 0; i < mapSizeX; ++i)
	{
		map[i] = new bool[mapSizeY];
	}
}

Game::~Game()
{
	for (size_t i = 0; i < mapSizeX; ++i)
	{
		delete [] map[i];
	}

	delete [] map;
}

void Game::Start()
{
	InitWindow();
	InitGL();
	CleanMap();

	sf::Clock deltaTimer;
	while(!exiting)
	{
		sf::Time deltaTime = deltaTimer.restart();
		EventUpdate(deltaTime.asSeconds());
		if (!paused){LogicUpdate(deltaTime.asSeconds());}
		Draw(deltaTime.asSeconds());
	}

	window.close();
}

void Game::InitWindow()
{
	window.create(sf::VideoMode(1024, 768), "Life2");
	window.setFramerateLimit(10);
}

void Game::InitGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.getSize().x, window.getSize().y, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::CleanMap()
{
	for (int x = 0; x < mapSizeX; ++x)
	{
		for (int y = 0; y < mapSizeY; ++y)
		{
			map[x][y] = false;
		}
	}
}

void Game::EventUpdate(float deltaTime)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			exiting = true;
		}
		if (event.type == sf::Event::Resized)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, event.size.width, event.size.height, 0, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glViewport(0, 0, event.size.width, event.size.height);
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				paused = !paused;
			}
			if (event.key.code == sf::Keyboard::G)
			{
				grid = !grid;
			}
			if (event.key.code == sf::Keyboard::Q)
			{
				exiting = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				HandleClick(event.mouseButton.x, event.mouseButton.y);
			}	
		}
	}
}

void Game::HandleClick(int x, int y)
{
	// He-he ;D
	int tmpX = static_cast<int>(static_cast<float>(x) / (static_cast<float>(window.getSize().x / static_cast<float>(mapSizeX))));
	int tmpY = static_cast<int>(static_cast<float>(y) / (static_cast<float>(window.getSize().y / static_cast<float>(mapSizeY))));
	
	map[tmpX][tmpY] = !map[tmpX][tmpY];
}

void Game::LogicUpdate(float deltaTime)
{
	bool tmp[mapSizeX][mapSizeY];

	for (int x = 0; x < mapSizeX; ++x)
	{
		for (int y = 0; y < mapSizeY; ++y)
		{
			int neighbors = CountNeighbors(x, y);
			if (map[x][y])
			{
				if (neighbors == 2 || neighbors == 3)
				{
					tmp[x][y] = true;
				}
				else
				{
					tmp[x][y] = false;
				}
			}
			else
			{
				if (neighbors == 3)
				{
					tmp[x][y] = true;
				}
				else
				{
					tmp[x][y] = false;
				}
			}
		}
	}

	for (int x = 0; x < mapSizeX; ++x)
	{
		for (int y = 0; y < mapSizeY; ++y)
		{
			map[x][y] = tmp[x][y];
		}
	}
}

int Game::CountNeighbors(int x, int y)
{
	int count = 0;
	if (GetOrganism(x, y + 1)){count++;} //Top
	if (GetOrganism(x, y - 1)){count++;} //Down
	if (GetOrganism(x + 1, y)){count++;} //Right
	if (GetOrganism(x - 1, y)){count++;} //Left

	if (GetOrganism(x + 1, y + 1)){count++;} //Top right
	if (GetOrganism(x - 1, y + 1)){count++;} //Top left
	if (GetOrganism(x + 1, y - 1)){count++;} //Down right
	if (GetOrganism(x - 1, y - 1)){count++;} //Down left

	return count;
}

bool Game::GetOrganism(int x, int y)
{
	int tx = x;
	int ty = y;

	while (tx > (mapSizeX - 1)){tx -= mapSizeX;}
	while (tx < 0){tx += mapSizeX;}
	while (ty > (mapSizeY - 1)){ty -= mapSizeY;}
	while (ty < 0){ty += mapSizeY;}

	return map[tx][ty];
}

void Game::Draw(float deltaTime)
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
			if (map[x][y])
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
		DrawGrid();
	}

	window.display();
}

void Game::DrawGrid()
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