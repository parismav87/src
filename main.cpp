#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "GameEngine.h"

using namespace std;

static bool ParseMove(string input, Move& result) //function that check if the input has the right format
{
	stringstream stream(input);
	int coords[4];
	for (int i = 0; i < 4; ++i)
	{
		try
		{
			string coord;
			if (!getline(stream, coord, ','))
				return false;
			coords[i] = stoi(coord); // string to int
		}
		catch (exception ex)
		{
			return false;
		}
	}
	result = { coords[1], coords[0], coords[3], coords[2] };
	return true;
}


static Move AskForNextMove(const GameEngine& map)
{
	bool validMove = false;
	Move move = { 0, 0, 0, 0 };
	do
	{
		system("cls");

		cout << "Input your next move:" << endl;

		map.printBoard();

		cout << "For example: \"0,0,1,0\" switches (row 0, column 0) and (row 1, column 0)." << endl;

		string input;
		cin >> input;

		if (!ParseMove(input, move))
		{
			cout << "Wrong format! Try again..." << endl;
			system("pause");
		}
		else if (!map.isValidMove(move))
		{
			cout << "Invalid move! Try again..." << endl;
			system("pause");
		}
		else if (!map.isMatchingMove(move))
		{
			cout << "Move does not make 3-in-a-row! Try again..." << endl;
			system("pause");
		}
		else
		{
			validMove = true;
		}
	} while (!validMove);
	return move;
}

int main()
{
	GameEngine map("C:\\Users\\Willeke\\Desktop\\map5.txt", "C:\\Users\\Willeke\\Desktop\\future5.txt");

	while (true)
	{
		Move move = AskForNextMove(map);
		map.makeMove(move);

		int matches = map.resolveMatches();
		while (matches > 0)
		{
			system("cls");
			if (matches == 1)
			{
				cout << "You made one match:" << endl;
			}
			else
			{
				cout << "You made " << matches << " matches:" << endl;
			}
			map.dropTiles();
			map.printBoard();
			system("pause");
			matches = map.resolveMatches();

		}
		map.dropTiles();
	}

	return 0;
}
