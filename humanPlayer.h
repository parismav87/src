#pragma once

#include "player.h"

class HumanPlayer : public Player
{
public:
	Move getNextMove(const Board& board) override;
};
