#pragma once

class Map
{
public:
	Map(int x, int y);
	~Map();
	void Update();
	bool Get(int x, int y);
	void Set(int x, int y, bool value);

private:

	int CountNeighbors(int x, int y);
	int m_SizeX;
	int m_SizeY;

	bool* m_Map;
	bool* m_Tmp;
};