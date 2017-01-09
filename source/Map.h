#pragma once

#include <vector>

class Map
{
public:
	enum CellState
	{
		Empty,
		Set
	};
public:
	Map(std::size_t sizeX, std::size_t sizeY);

	void update();

	CellState get(int x, int y) const;
	void set(int x, int y, CellState value);
private:
	unsigned countNeighbors(int x, int y) const;

	void setTemporary(int x, int y, CellState value);

	void swapData();
private:
	std::size_t sizeX;
	std::size_t sizeY;

	std::vector<CellState> data;
	std::vector<CellState> temp;
};
