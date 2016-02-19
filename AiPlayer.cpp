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
	fringe.emplace(Node{unique_ptr<GameBoard>{new GameBoard{board}},
		board.usedSpaces(),
		board.currentPlayer() == player});

	while (!fringe.empty())
	{
		if (fringe.front().getDepth() == 0 || fringe.front().isTerminalState())
		{
			// TODO: Evaluate the node heuristic and use it to update the parent
		}
		else if (fringe.front().hasNextNode())
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

/*
01 function alphabeta(node, depth, α, β, maximizingPlayer)
02      if depth = 0 or node is a terminal node
03          return the heuristic value of node
04      if maximizingPlayer
05          v := -∞
06          for each child of node
07              v := max(v, alphabeta(child, depth - 1, α, β, FALSE))
08              α := max(α, v)
09              if β ≤ α
10                  break (* β cut-off *)
11          return v
12      else
13          v := ∞
14          for each child of node
15              v := min(v, alphabeta(child, depth - 1, α, β, TRUE))
16              β := min(β, v)
17              if β ≤ α
18                  break (* α cut-off *)
19          return v
*/
