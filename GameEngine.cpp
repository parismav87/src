#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "GameEngine.h"

static bool ReadLine(vector<int>& row, istream& stream) //static function promises to not use this function outside of this header
{
	row.clear();
	string line, tile;

	if (!getline(stream, line))
		return false;

	stringstream lineStream(line);
	while (getline(lineStream, tile, ','))
		row.push_back(stoi(tile));

	return true;
}

static void ReadLines(vector<vector<int>>& columns, istream& stream)
{
	vector<int> row;
	while (ReadLine(row, stream))
	{
		for (int x = 0; x < (int)row.size(); ++x)
			columns[x].push_back(row[x]);
	}
}

GameEngine::GameEngine(string tileMapPath, string futureTileMapPath)
{
	fstream stream(futureTileMapPath);

	// Read the first line to figure out the width of the file.
	vector<int> firstRow;
	ReadLine(firstRow, stream);
	int mapWidth = firstRow.size();

	// Create temporary columns to hold the tile data and copy the first row.
	vector<vector<int>> columns(mapWidth);
	for (int x = 0; x < mapWidth; ++x)
		columns[x].push_back(firstRow[x]);

	// Read remaining lines from the future file.
	ReadLines(columns, stream);

	// Read lines from the map file.
	stream = fstream(tileMapPath);
	ReadLines(columns, stream);

	// Reverse each column, so the bottom of the board is at index 0.
	for (vector<int>& column : columns)
		reverse(column.begin(), column.end());

	// Create columns from the parsed data.
	mySize = mapWidth; // assume map width and height are the same.
	for (int x = 0; x < mapWidth; ++x)
		myColumns.emplace_back(columns[x], mySize);
}

void GameEngine::printBoard() const //A "const function", denoted with the keyword const after a function declaration, makes it a compiler error for this class function to change a member variable of the class. However, reading of a class variables is okay inside of the function, but writing inside of this function will generate a compiler error.
{
	cout << endl;

	// Row numbers and board.
	for (int row = mySize - 1; row >= 0; --row)
	{
		cout << " " << (row % 10) << " | ";  //row%10 so numbers don't exceed 9 and two digit numbers won't mess up the markup
		for (int col = 0; col < mySize; ++col)
		{
			int tile = myColumns[col][row];
			if (tile == 0)
			{
				cout << "- ";
			}
			else
			{
				cout << tile << " ";
			}
		}
		cout << endl;
	}

	// Horizontal line below the board.
	cout << "   +-";
	for (int col = 0; col < mySize; ++col)
	{
		cout << "--";
	}
	cout << endl;

	// Column numbers.
	cout << "     ";
	for (int col = 0; col < mySize; ++col)
	{
		cout << (col % 10) << " ";
	}
	cout << endl << endl;
}

bool GameEngine::isValidTile(int x, int y) const
{
	return x >= 0
		&& y >= 0
		&& x < mySize
		&& y < mySize
		&& myColumns[x][y] != 0;
}

static int GetTileAfterMove(const GameEngine& map, int x, int y, Move move) //static member functions are not attached to a particular object, they can be called directly by using the class name and the scope resolution operator.
{
	if (x == move.x1 && y == move.y1)
	{
		x = move.x2;
		y = move.y2;
	}
	else if (x == move.x2 && y == move.y2)
	{
		x = move.x1;
		y = move.y1;
	}
	return map[x][y];
}

bool GameEngine::isValidMove(Move move) const
{
	if (!isValidTile(move.x1, move.y1) || !isValidTile(move.x2, move.y2))
		return false;

	bool isHorizontalMove = abs(move.x1 - move.x2) == 1 && move.y1 - move.y2 == 0;
	bool isVerticalMove = abs(move.y1 - move.y2) == 1 && move.x1 - move.x2 == 0;

	if (!isHorizontalMove && !isVerticalMove)
		return false;

	return true;
}

bool GameEngine::isMatchingMove(Move move) const
{
	if (!isValidMove(move))
		return false;

	for (int y = 0; y < mySize; ++y)
	{
		for (int x = 1; x < mySize - 1; ++x)
		{
			int a = GetTileAfterMove(*this, x - 1, y, move);
			int b = GetTileAfterMove(*this, x, y, move);
			int c = GetTileAfterMove(*this, x + 1, y, move);

			if (a != 0 && a == b && a == c)
				return true;
		}
	}

	for (int x = 0; x < mySize; ++x)
	{
		for (int y = 1; y < mySize - 1; ++y)
		{
			int a = GetTileAfterMove(*this, x, y - 1, move);
			int b = GetTileAfterMove(*this, x, y, move);
			int c = GetTileAfterMove(*this, x, y + 1, move);

			if (a != 0 && a == b && a == c)
				return true;
		}
	}

	return false;
}

static bool IsHorizontalMatch(const GameEngine& map, int centerX, int y)
{
	int center = map[centerX][y];
	return center != 0
		&& map[centerX - 1][y] == center
		&& map[centerX + 1][y] == center;
}

static bool IsVerticalMatch(const GameEngine& map, int x, int centerY)
{
	int center = map[x][centerY];
	return center != 0
		&& map[x][centerY - 1] == center
		&& map[x][centerY + 1] == center;
}

void GameEngine::makeMove(Move move)
{
	int temp = myColumns[move.x1][move.y1];
	myColumns[move.x1][move.y1] = myColumns[move.x2][move.y2];
	myColumns[move.x2][move.y2] = temp;
}

int GameEngine::resolveMatches()
{
	GameEngine result(*this); //make a copy of the gamemap on which the moves can be performed

	int numMatches = 0;

	for (int y = 0; y < mySize; ++y)
	{
		for (int x = 1; x < mySize - 1; ++x)
		{
			if (IsHorizontalMatch(*this, x, y))
			{
				result[x - 1][y] = 0;
				result[x][y] = 0;
				result[x + 1][y] = 0;
				++numMatches;
			}
		}
	}
	for (int x = 0; x < mySize; ++x)
	{
		for (int y = 1; y < mySize - 1; ++y)
		{
			if (IsVerticalMatch(*this, x, y))
			{
				result[x][y - 1] = 0;
				result[x][y] = 0;
				result[x][y + 1] = 0;
				++numMatches;
			}
		}
	}

	swap(myColumns, result.myColumns); //if all matches have been resolved, make the copy of the map, the real map

	return numMatches;
}

void GameEngine::dropTiles()
{
	for (auto& column : myColumns) //auto: the type of the variable that is being declared will be automatically deduced from its initializer.
		column.dropTiles();
}

int GameEngine::size() const
{
	return mySize;
}

TileColumn& GameEngine::operator[] (int index) //class function operator to overload the operator (cancels compiler warnings and throws an exception if future tiles are accessed)
{
	return myColumns[index];
}

const TileColumn& GameEngine::operator[] (int index) const //constant version of class function operator to overload the operator (cancels compiler warnings and throws an exception if future tiles are accessed)
{
	return myColumns[index];
}
