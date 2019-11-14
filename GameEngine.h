# pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Common.h"
#include "player.h"

using namespace std;

// Contains a set of tile columns.
class GameEngine
{
public:
	GameEngine(string tileMapPath, string futureTileMapPath, Player& player);

	bool isValidTile(int x, int y) const;

	bool isValidMove(Move move);

	bool isMatchingMove(Move move);

	void makeMove(Move move);

	int resolveMatches();

	void dropTiles();

	void printBoard() const;

	int size() const;
	
	int score() const;

	void gameLoop();

	int getTileAfterMove(int x, int y, Move move);

	bool isHorizontalMatch(int centerX, int y);

	bool isVerticalMatch(int x, int centerY);

	int calculateNewScore(int matches);

	bool movesLeft();

	bool isPossibleMove(const Move& move);

private:
	int mySize;
	vector<Column> map;
	int myScore;
	bool gameIsRunning;
	Player& myPlayer;
};
