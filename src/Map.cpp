#include "Map.h"


Map::Map(int size_x, int size_y)
{
	m_SizeX = size_x;
	m_SizeY = size_y;
	m_Map = new bool[size_x * size_y];
	m_Tmp = new bool[size_x * size_y];
}

Map::~Map()
{
	delete [] m_Map;
}

void Map::Update()
{
	for (int x = 0; x < m_SizeX; ++x)
	{
		for (int y = 0; y < m_SizeY; ++y)
		{
			int neighbors = CountNeighbors(x, y);
			if (this->Get(x, y))
			{
				if (neighbors == 2 || neighbors == 3)
				{
					m_Tmp[y * m_SizeX + x] = true;
				}
				else
				{
					m_Tmp[y * m_SizeX + x] = false;
				}
			}
			else
			{
				if (neighbors == 3)
				{
					m_Tmp[y * m_SizeX + x] = true;
				}
				else
				{
					m_Tmp[y * m_SizeX + x] = false;
				}
			}
		}
	}

	for (int x = 0; x < m_SizeX; ++x)
	{
		for (int y = 0; y < m_SizeY; ++y)
		{
			m_Map[y * m_SizeX + x] = m_Tmp[y * m_SizeX + x];
		}
	}
}

int Map::CountNeighbors(int x, int y)
{
	int count = 0;
	if (this->Get(x, y + 1)){count++;} //Top
	if (this->Get(x, y - 1)){count++;} //Down
	if (this->Get(x + 1, y)){count++;} //Right
	if (this->Get(x - 1, y)){count++;} //Left

	if (this->Get(x + 1, y + 1)){count++;} //Top right
	if (this->Get(x - 1, y + 1)){count++;} //Top left
	if (this->Get(x + 1, y - 1)){count++;} //Down right
	if (this->Get(x - 1, y - 1)){count++;} //Down left

	return count;
}

bool Map::Get(int x, int y)
{
	int tx = x;
	int ty = y;

	while (tx > (m_SizeX - 1)){tx -= m_SizeX;}
	while (tx < 0){tx += m_SizeX;}
	while (ty > (m_SizeY - 1)){ty -= m_SizeY;}
	while (ty < 0){ty += m_SizeY;}

	return m_Map[ty * m_SizeX + tx];
}

void Map::Set(int x, int y, bool value)
{
	int tx = x;
	int ty = y;

	while (tx > (m_SizeX - 1)){tx -= m_SizeX;}
	while (tx < 0){tx += m_SizeX;}
	while (ty > (m_SizeY - 1)){ty -= m_SizeY;}
	while (ty < 0){ty += m_SizeY;}

	m_Map[ty * m_SizeX + tx] = value;
}

