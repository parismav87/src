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

static void ReadLines(vector<Column>& columns, istream& stream)
{
	vector<int> row;
	while (ReadLine(row, stream))
	{
		for (int x = 0; x < (int)row.size(); ++x)
			columns[x].push_back(row[x]);
	}
}

GameEngine::GameEngine(string tileMapPath, string futureTileMapPath, Player& player)
		  : myPlayer(player) //directly assigns the value (must be done for a reference), instead of doing that during the code of the constructor (avoids making two copies)
{
	fstream stream(futureTileMapPath);

	// Read the first line to figure out the width of the file.
	vector<int> firstRow;
	ReadLine(firstRow, stream);
	int mapWidth = firstRow.size();

	// Create temporary columns to hold the tile data and copy the first row.
	vector<Column> columns(mapWidth);
	for (int x = 0; x < mapWidth; ++x)
		columns[x].push_back(firstRow[x]);

	// Read remaining lines from the future file.
	ReadLines(columns, stream);

	// Read lines from the map file.
	stream = fstream(tileMapPath);
	ReadLines(columns, stream);

	// Reverse each column, so the bottom of the board is at index 0.
	for (Column& column : columns)
		reverse(column.begin(), column.end());

	map = columns;

	// Create columns from the parsed data.
	mySize = mapWidth; // assume map width and height are the same.

	gameLoop();
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
			int tile = map[col][row];
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
		&& map[x][y] != 0;
}

int GameEngine::getTileAfterMove(int x, int y, Move move) //static member functions are not attached to a particular object, they can be called directly by using the class name and the scope resolution operator.
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

bool GameEngine::isValidMove(Move move)
{
	if (!isValidTile(move.x1, move.y1) || !isValidTile(move.x2, move.y2))
		return false;

	bool isHorizontalMove = abs(move.x1 - move.x2) == 1 && move.y1 - move.y2 == 0;
	bool isVerticalMove = abs(move.y1 - move.y2) == 1 && move.x1 - move.x2 == 0;

	if (!isHorizontalMove && !isVerticalMove)
		return false;

	return true;
}

bool GameEngine::isMatchingMove(Move move)
{
	if (!isValidMove(move))
		return false;

	for (int y = 0; y < mySize; ++y)
	{
		for (int x = 1; x < mySize - 1; ++x)
		{
			int a = getTileAfterMove(x - 1, y, move);
			int b = getTileAfterMove(x, y, move);
			int c = getTileAfterMove(x + 1, y, move);

			if (a != 0 && a == b && a == c)
				return true;
		}
	}

	for (int x = 0; x < mySize; ++x)
	{
		for (int y = 1; y < mySize - 1; ++y)
		{
			int a = getTileAfterMove(x, y - 1, move);
			int b = getTileAfterMove(x, y, move);
			int c = getTileAfterMove(x, y + 1, move);

			if (a != 0 && a == b && a == c)
				return true;
		}
	}

	return false;
}

bool GameEngine::isHorizontalMatch(int centerX, int y)
{
	int center = map[centerX][y];
	return center != 0
		&& map[centerX - 1][y] == center
		&& map[centerX + 1][y] == center;
}

bool GameEngine::isVerticalMatch(int x, int centerY)
{
	int center = map[x][centerY];
	return center != 0
		&& map[x][centerY - 1] == center
		&& map[x][centerY + 1] == center;
}

bool GameEngine::isPossibleMove(const Move& move)
{
	if (!isValidTile(move.x1, move.y1) || !isValidTile(move.x2, move.y2))
	{
		cout << "Invalid tile, the tile must be in bounds and not empty!" << endl;
		return false;
	}
	else if (!isValidMove(move))
	{
		cout << "Invalid move! Try again..." << endl;
		return false;
	}
	else if (!isMatchingMove(move))
	{
		cout << "Move does not make 3-in-a-row! Try again..." << endl;
		return false;
	}
	return true;
}

void GameEngine::makeMove(Move move)
{
	swap(map[move.x1][move.y1], map[move.x2][move.y2]);
}

int GameEngine::resolveMatches()
{
	GameEngine result(*this); //make a copy of the gamemap on which the moves can be performed

	int numMatches = 0;

	for (int y = 0; y < mySize; ++y)
	{
		for (int x = 1; x < mySize - 1; ++x)
		{
			if (isHorizontalMatch(x, y))
			{
				result.map[x - 1][y] = 0;
				result.map[x][y] = 0;
				result.map[x + 1][y] = 0;
				++numMatches;
			}
		}
	}
	for (int x = 0; x < mySize; ++x)
	{
		for (int y = 1; y < mySize - 1; ++y)
		{
			if (isVerticalMatch(x, y))
			{
				result.map[x][y - 1] = 0;
				result.map[x][y] = 0;
				result.map[x][y + 1] = 0;
				++numMatches;
			}
		}
	}

	swap(map, result.map); //if all matches have been resolved, make the copy of the map, the real map

	numberOfTilesThatMatch(); //function that counts how many tiles need to be broken/match

	return numMatches;
}

int GameEngine::numberOfTilesThatMatch() 
{
	int numberOfMatchingTiles = 0;
	for (int col = 0; col < mySize; ++col)
	{
		for (int row = 0; row < mySize; ++row)
		{
			if (map[col][row] == 0)
			{
				numberOfMatchingTiles += 1;
			}
		}
	}

	return numberOfMatchingTiles;
}

void GameEngine::dropTiles()
{
	for (int col = 0; col < map.size(); ++col)
	{
		for (int row = 0; row < map[0].size() - 1; ++row)
		{
			if (map[col][row] != 0)
				continue;

			int rowAbove = row + 1;
			while (rowAbove < map[0].size() - 1 && map[col][rowAbove] == 0) //checks if the tile above the cuurent one (that is 0) is also 0, so swapping tiles can actually succeed
				rowAbove++;

			swap(map[col][row], map[col][rowAbove]);
		}
	}
}

int GameEngine::size() const
{
	return mySize;
}

int GameEngine::score() const
{
	return myScore;
}

bool GameEngine::movesLeft()
{
	int numberMovesLeft = 0;
	for (int row = 0; row < mySize; ++row)
	{
		for (int col = 0; col < mySize; ++col)
		{
			Move move;
			move.x1 = row;
			move.y1 = col;
			move.x2 = row + 1;
			move.y2 = col;
			if (isMatchingMove(move))
			{
				numberMovesLeft += 1;
			}
		}
	}

	for (int col = 0; col < mySize; ++col)
	{
		for (int row = 0; row < mySize; ++row)
		{
			Move move;
			move.x1 = row;
			move.y1 = col;
			move.x2 = row;
			move.y2 = col + 1;
			if (isMatchingMove(move))
			{
				numberMovesLeft += 1;
			}
		}
	}
	if (numberMovesLeft == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int GameEngine::calculateNewScore(int matches)
{
	int addScore = 0;
	for (int i = 1; i <= matches; i++)
	{
		addScore += i;
	}
	return addScore;
}

void GameEngine::gameLoop()
{
	myScore = 0;
	gameIsRunning = true;
	while (gameIsRunning)
	{
		printBoard();

		//make a copy of the visible board
		Board board;
		board.size = mySize;
		for (int col = 0; col < mySize; ++col)
		{
			Column column;
			for (int row = 0; row < mySize; ++row)
			{
				column.push_back(map[col][row]);
			}
			board.columns.push_back(column);
		}

		//ask the player for the next move
		Move move;
		while (true)
		{
			move = myPlayer.getNextMove(board);
			if (isPossibleMove(move))
				break;
			cout << "Try again..." << endl;
		}

		makeMove(move);

		int matches = resolveMatches();
		//int totalMatches = 0;
		int newMatchesWithoutInput = 1;
		int numberOfTilesMatching = 0;
		while (matches > 0)
		{
			system("cls");
			if (matches == 1)
			{
				cout << "You made one match!" << endl;
			}
			else
			{
				cout << "You made " << matches << " matches!" << endl;
			}
			cout << "Matches made: " << endl;
			numberOfTilesMatching = numberOfTilesThatMatch();
			myScore += numberOfTilesMatching * newMatchesWithoutInput;
			newMatchesWithoutInput += 1;
			printBoard();
			dropTiles();
			cout << "New tiles have dropped in, making the new board:" << endl;
			printBoard();
			system("pause");
			system("cls");
			//totalMatches += matches;
			matches = resolveMatches();
		}
		//myScore += calculateNewScore(totalMatches);
		gameIsRunning = movesLeft();
		cout << "Your score is: " << myScore << endl;

		if (!gameIsRunning)
		{
			system("cls");
			printBoard();
			cout << "There are no more moves left to make: GAME OVER" << endl;
			cout << "your final score was: " << myScore << endl;
			system("pause");
		}
	}
}