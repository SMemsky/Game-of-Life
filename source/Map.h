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

	CellState get(int x, int y) const;
	void set(int x, int y, CellState value);

	void swap(Map & other);
private:
	std::size_t sizeX;
	std::size_t sizeY;

	std::vector<CellState> data;
};
