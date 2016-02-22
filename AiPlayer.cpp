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
	// Limiting the search depth to 1 seems to lead to optimal play.
	// Because the AI assumes the human plays perfectly, allowing a deeper
	// search causes it to dismiss options that could lead to victory
	// when the human plays poorly.
	fringe.emplace(Node{board, 1, true});

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
				break;
			}
		}
	}

	return fringe.top().getBestMove();
}
