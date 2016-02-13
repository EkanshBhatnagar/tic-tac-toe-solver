/*
 * AiPlayer.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <list>
#include "AiPlayer.h"
#include "Move.h"
#include "GameBoard.h"
using namespace std;

static list<GameBoard> successorStates(const GameBoard& board);

AiPlayer::AiPlayer(bool playerX) : Player{playerX}
{
}

AiPlayer::~AiPlayer()
{
}

Move AiPlayer::nextMove(const GameBoard& board)
{

}

// Static, non-member helper functions for this file only
static list<GameBoard> successorStates(const GameBoard& board)
{
	auto successors = list<GameBoard>{};

	for (auto x = 0; x < 3; ++x)
	{
		for (auto y = 0; y < 3; ++y)
		{
			if (board.get(x, y) == ' ')
			{
				auto s = GameBoard{board};
				s.makeMove(Move{x, y});
				successors.push_back(s);
			}
		}
	}

	return successors;
}
