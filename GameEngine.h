#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "TileColumn.h"
#include "Common.h"

// Contains a set of tile columns.
class GameEngine
{
public:
	GameEngine(string tileMapPath, string futureTileMapPath);

	TileColumn& operator[] (int index);

	const TileColumn& operator[] (int index) const;

	bool isValidTile(int x, int y) const;

	bool isValidMove(Move move) const;

	bool isMatchingMove(Move move) const;

	void makeMove(Move move);

	int resolveMatches();

	void dropTiles();

	void printBoard() const;

	int size() const;

private:
	int mySize;
	vector<TileColumn> myColumns;
};
