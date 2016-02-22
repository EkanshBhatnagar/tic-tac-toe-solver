/*
 * AiPlayer.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <stack>
#include <list>
#include "AiPlayer.h"
#include "Move.h"
#include "GameBoard.h"
#include "Node.h"

using namespace std;

AiPlayer::AiPlayer(bool playerX) : Player{playerX}
{
}

AiPlayer::~AiPlayer()
{
}

Move AiPlayer::nextMove(const GameBoard& board)
{
	auto fringe = stack<Node>{};
	// Use a depth-limited search of 3
	fringe.emplace(Node{board, min(3, 9 - board.usedSpaces()), true});

	while (!fringe.empty())
	{
		if (fringe.top().hasNextNode())
		{
			// Expand the next node, and make that the top of the stack
			fringe.top().expandNextNode(fringe);
			// Following ordinary stack rules, we can only ever operate on the
			// top element, so go back to the start of the loop.
		}
		else
		{
			if (fringe.size() > 1)
			{
				fringe.top().updateParent();
				fringe.pop();
			}
			else
			{
				return fringe.top().getBestMove();
			}
		}
	}
}
