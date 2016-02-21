/*
 * AiPlayer.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <queue>
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
	auto nodes = list<Node>{};
	auto fringe = queue<Node>{};

	// Add the root node
	fringe.emplace(Node{"   /   /   ",
		board.usedSpaces(),
		board.currentPlayer() == player});

	while (!fringe.empty())
	{
		if (fringe.front().hasNextNode())
		{
			// Expand the next node, and make that the top of the stack
			fringe.front().expandNextNode(fringe);
			// Following ordinary stack rules, we can only ever operate on the
			// top element, so go back to the start of the loop.
		}
		else
		{
			fringe.front().updateParent();

			// Done with the current node, so add it to our finished node list
			// and then pop it from the stack
			nodes.push_back(std::move(fringe.front()));
			fringe.pop();
		}
	}

	// Best move will be whatever child node gave the final alpha value to the root
	// We throw out the rest of the game tree because we'll need to recalculate it
	// once the opponent makes his move.

	return nodes.front().getBestMove();
}
