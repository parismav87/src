#pragma once

#include <vector>

using namespace std;

typedef vector<int> Column;

struct Move //struct (sort of mini class) which contains the move coordinates, so that only the move and not the coordinates have to be passed to a function
{
	int x1, y1, x2, y2;
};

struct Board
{
	int size;
	vector<Column> columns;
};