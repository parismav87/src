#include "TileColumn.h"

#include <stdexcept>

TileColumn::TileColumn(vector<int> tiles, int visibleTiles)
{
	myVisibleTiles = visibleTiles;
	myTiles = tiles;
}

void TileColumn::dropTiles()
{
	for (int row = 0; row < myTiles.size() - 1; ++row)
	{
		if (myTiles[row] != 0)
			continue;

		int rowAbove = row + 1;
		while (rowAbove < myTiles.size() - 1 && myTiles[rowAbove] == 0) //checks if the tile above the cuurent one (that is 0) is also 0, so swapping tiles can actually succeed
			rowAbove++;

		int temp = myTiles[row];
		myTiles[row] = myTiles[rowAbove];
		myTiles[rowAbove] = temp;
	}
}

int& TileColumn::operator[] (int index)
{
	if (index >= myVisibleTiles)
		throw out_of_range("Access to future tiles is forbidden!"); //throws an exception if the tile that was selected was out of bounds

	return myTiles[index];
}


int TileColumn::operator[] (int index) const
{
	if (index >= myVisibleTiles)
		throw out_of_range("Access to future tiles is forbidden!"); //throws an exception if the tile that was selected was out of bounds

	return myTiles[index];
}



