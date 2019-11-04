#pragma once

#include <vector>

using namespace std;

// A vertical column of tiles, including future tiles.
class TileColumn
{
public:
	TileColumn(vector<int> tiles, int visibleTiles);

	void dropTiles();

	int& operator[] (int index);

	int operator[] (int index) const;

private:
	int myVisibleTiles;
	vector<int> myTiles;
};
