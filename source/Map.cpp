#include "Map.h"

#include <utility>

Map::Map(std::size_t sizeX, std::size_t sizeY) :
	sizeX(sizeX),
	sizeY(sizeY),
	data(sizeX * sizeY, Empty),
	temp(sizeX * sizeY, Empty)
{}

void Map::update()
{
	for (unsigned x = 0; x < sizeX; ++x)
	{
		for (unsigned y = 0; y < sizeY; ++y)
		{
			unsigned neighbors = countNeighbors(x, y);

			if (get(x, y) == Set)
			{
				setTemporary(x, y,
					(neighbors == 2 || neighbors == 3) ? Set : Empty);
			}
			else
			{
				setTemporary(x, y, (neighbors == 3) ? Set : Empty);
			}
		}
	}

	swapData();
}

Map::CellState Map::get(int x, int y) const
{
	x %= sizeX;
	x = (x < 0) ? (x + sizeX) : x;
	y %= sizeY;
	y = (y < 0) ? (y + sizeY) : y;

	return data[x + y * sizeX];
}

void Map::set(int x, int y, CellState value)
{
	x %= sizeX;
	x = (x < 0) ? (x + sizeX) : x;
	y %= sizeY;
	y = (y < 0) ? (y + sizeY) : y;

	data[x + y * sizeX] = value;
}

unsigned Map::countNeighbors(int x, int y) const
{
	unsigned count = 0;

	if (get(x, y + 1)) { ++count; } //Top
	if (get(x, y - 1)) { ++count; } //Down
	if (get(x + 1, y)) { ++count; } //Right
	if (get(x - 1, y)) { ++count; } //Left

	if (get(x + 1, y + 1)) { ++count; } //Top right
	if (get(x - 1, y + 1)) { ++count; } //Top left
	if (get(x + 1, y - 1)) { ++count; } //Down right
	if (get(x - 1, y - 1)) { ++count; } //Down left

	return count;
}

void Map::setTemporary(int x, int y, CellState value)
{
	x %= sizeX;
	x = (x < 0) ? (x + sizeX) : x;
	y %= sizeY;
	y = (y < 0) ? (y + sizeY) : y;

	temp[x + y * sizeX] = value;
}

void Map::swapData()
{
	data.swap(temp);
}
