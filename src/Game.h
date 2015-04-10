#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void Start();


private:

	void InitWindow();
	void InitGL();
	void CleanMap();

	void EventUpdate(float deltaTime);
	void HandleClick(int x, int y);
	void LogicUpdate(float deltaTime);
	int CountNeighbors(int x, int y);
	bool GetOrganism(int x, int y);
	void Draw(float deltaTime);
	void DrawGrid();

	sf::RenderWindow window;

	bool exiting;
	bool paused;
	bool grid;

	const int mapSizeX;
	const int mapSizeY;

	bool** map;
};