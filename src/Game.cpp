#include <SFML/OpenGL.hpp>
#include <iostream>
using std::cout;
using std::endl;

#include "Game.h"

Game::Game(int x, int y, int framerate) :
	window(),
	exiting(false),
	paused(true),
	grid(true),
	m_Framerate(framerate),
	mapSizeX(x),
	mapSizeY(y),
	m_Map(nullptr)
{
	m_Map = new Map(x, y);
}

Game::~Game()
{
	
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
		if (!paused)
		{
			LogicUpdate(deltaTime.asSeconds());
		}
		Draw(deltaTime.asSeconds());
	}

	window.close();
}

void Game::InitWindow()
{
	window.create(sf::VideoMode(1000, 1000), "Life2");
	window.setFramerateLimit(m_Framerate);
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
	bool numb[3] = {false, true, true};
	int counterX = 0;
	int counterY = 0;
	for (int x = 0; x < mapSizeX; ++x)
	{
		counterY = 0;
		if (counterX == 0)
		{
			for (int y = 0; y < mapSizeY; ++y)
			{
				m_Map->Set(x, y, false);
			}
			counterX++;
		}
		else
		{
			for (int y = 0; y < mapSizeY; ++y)
			{
				m_Map->Set(x, y, numb[counterY]);
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
			if (event.key.code == sf::Keyboard::R)
			{
				CleanMap();
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
	
	m_Map->Set(tmpX, tmpY, !m_Map->Get(tmpX, tmpY));
}

void Game::LogicUpdate(float deltaTime)
{
	m_Map->Update();
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
			if (m_Map->Get(x, y))
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