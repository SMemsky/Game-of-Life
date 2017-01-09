#include "Map.h"

#include <cassert>
#include <limits>
#include <utility>

Map::Map(std::size_t sizeX, std::size_t sizeY) :
	sizeX(sizeX),
	sizeY(sizeY),
	data(sizeX * sizeY, Empty)
{
	assert(static_cast<unsigned>(std::numeric_limits<int>::max()) > sizeX);
	assert(static_cast<unsigned>(std::numeric_limits<int>::max()) > sizeY);
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

void Map::swap(Map & other)
{
	data.swap(other.data);
}
