#pragma once

#include <SFML/Graphics.hpp>

#include "Map.h"

class Game
{
public:
	Game(int x, int y, int framerate);
	~Game();

	void Start();

private:

	void InitWindow();
	void InitGL();
	void CleanMap();

	void EventUpdate(float deltaTime);
	void HandleClick(int x, int y);
	void LogicUpdate(float deltaTime);
	void Draw(float deltaTime);
	void DrawGrid();

	sf::RenderWindow window;

	bool exiting;
	bool paused;
	bool grid;

	const int m_Framerate;

	const int mapSizeX;
	const int mapSizeY;

	Map* m_Map;
};