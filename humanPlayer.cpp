#include "humanPlayer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

static bool ParseMove(string input, Move& result)
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
			coords[i] = stoi(coord);
		}
		catch (exception ex)
		{
			return false;
		}
	}
	result = { coords[1], coords[0], coords[3], coords[2] };
	return true;
}

Move HumanPlayer::getNextMove(const Board& board)
{
	cout << "Input your next move:" << endl;
	cout << "For example: \"0,0,1,0\" switches (row 0, column 0) and (row 1, column 0)." << endl;

	Move move = { 0, 0, 0, 0 };
	while (true)
	{
		string input;
		cin >> input;

		if (ParseMove(input, move))
			break;

		cout << "Wrong format! Try again..." << endl;
	}
	return move;
}