/*
 * Node.cpp
 *
 *  Created on: 2016-02-13
 *      Author: derek
 */

#include "Node.h"
#include "Move.h"
#include "GameBoard.h"
#include <queue>
#include <memory>
#include <limits>
#include <cstdint>
#include <cassert>
using namespace std;

Node::Node(std::unique_ptr<GameBoard> state, Node* const parent,
		std::unique_ptr<Move> action, uint8_t depth,
		int8_t alpha, int8_t beta, bool maximizer)
	: state{std::move(state)},
	  parent{parent},
	  action{std::move(action)},
	  depth{depth},
	  alpha{alpha},
	  beta{beta},
	  maximizer{maximizer},
	  bestChildValue{maximizer ? std::numeric_limits<int8_t>::min()
	      		: std::numeric_limits<int8_t>::max()},
	  nextNodeMove{0, 0},
	  bestChild{nullptr}
{
}

// For a root node
Node::Node(unique_ptr<GameBoard> state, uint8_t depth, bool maximizer)
	: Node(std::move(state), nullptr, nullptr, depth, std::numeric_limits<int8_t>::min(),
			std::numeric_limits<int8_t>::max(), maximizer)
{
}

// We will expand child nodes until we have explored all possible moves,
// or beta > alpha. Note that beta is our strongest lower bound and alpha
// is our strongest upper bound, so beta > alpha indicates a game state that
// any sane opponent will never let happen.
bool Node::hasNextNode() const
{
	return get<0>(nextNodeMove) <= 2 && get<1>(nextNodeMove) <= 2
			&& beta > alpha;
}

void Node::expandNextNode(queue<Node>& fringe)
{
	for (auto x = get<0>(nextNodeMove); x < 3; ++x)
	{
		for (auto y = get<1>(nextNodeMove); y < 3; ++y)
		{
			if (state->get(x, y) == ' ')
			{
				// Add child state to the fringe
				auto newBoard = unique_ptr<GameBoard>{new GameBoard{*state}};
				auto newMove = unique_ptr<Move>{new Move{x, y}};
				newBoard->makeMove(*newMove);
				fringe.emplace(Node{std::move(newBoard), this, std::move(newMove),
					depth > 0 ? depth - 1 : 0, alpha, beta, !maximizer});

				// Increment the next move coordinates
				if (x < 2)
				{
					nextNodeMove = decltype(nextNodeMove){ x + 1, y };
				}
				else if (y < 2)
				{
					nextNodeMove = decltype(nextNodeMove){ 0, y + 1 };
				}
				else
				{
					// Invalid move
					nextNodeMove = decltype(nextNodeMove){ 3, 3 };
				}
			}
		}
	}
}

uint8_t Node::getValue() const
{
	if (depth == 0 || isTerminalState())
	{
		return getHeuristic();
	}
	else if (maximizer)
	{
		return beta;
	}
	else
	{
		return alpha;
	}
}

uint8_t Node::getHeuristic() const
{
	return 0; // TODO: Implement heuristics
}

void Node::updateParent()
{
	if (parent)
	{
		parent->update(*this);
	}
}

void Node::update(const Node& child)
{
	if (maximizer)
	{
		if (child.getValue() > bestChildValue)
		{
			bestChildValue = child.getValue();
			bestChild = &child;
			alpha = std::max(alpha, bestChildValue);
		}
	}
	else
	{
		if (child.getValue() < bestChildValue)
		{
			bestChildValue = child.getValue();
			bestChild = &child;
			beta = std::min(beta, bestChildValue);
		}
	}
}

bool Node::isTerminalState() const
{
	return state->endState() != ttt::EndState::NotOver;
}

uint8_t Node::getDepth() const
{
	return depth;
}

Move Node::getBestMove() const
{
	assert(bestChild != nullptr);
	return *bestChild->action;
}
