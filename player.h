#pragma once

#include "common.h"

class Player
{
public:
	virtual Move getNextMove(const Board& board) = 0;
};