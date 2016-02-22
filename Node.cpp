/*
 * Node.cpp
 *
 *  Created on: 2016-02-13
 *      Author: derek
 */

#include <ostream>
#include "Node.h"
#include "Move.h"
#include "GameBoard.h"
#include "Heuristic.h"
#include <stack>
#include <memory>
#include <limits>
#include <cstdint>
#include <string>
#include <cassert>
using namespace std;

Node::Node(std::unique_ptr<GameBoard> state, Node* const parent,
		std::unique_ptr<Move> action, uint8_t depth,
		Heuristic alpha, Heuristic beta, bool maximizer)
	: state{std::move(state)},
	  parent{parent},
	  action{std::move(action)},
	  depth{depth},
	  alpha{alpha},
	  beta{beta},
	  maximizer{maximizer},
	  nextNodeMove{0, 0},
	  bestMove{nullptr}
{
	// If they called it with a null GameBoard,
	// they probably want a blank game state
	if (state == nullptr)
	{
		state.reset(new GameBoard);
	}
}

// For a root node
Node::Node(string state, uint8_t depth, bool maximizer)
	: Node(unique_ptr<GameBoard>{new GameBoard{state}},
			nullptr, nullptr, depth, Heuristic::min(),
			Heuristic::max(), maximizer)
{
}

// For a root node
Node::Node(const GameBoard& state, uint8_t depth, bool maximizer)
	: Node(make_unique<GameBoard>(state),
			nullptr, nullptr, depth, Heuristic::min(),
			Heuristic::max(), maximizer)
{
}

// We will expand child nodes until we have explored all possible moves,
// or beta > alpha. Note that beta is our strongest lower bound and alpha
// is our strongest upper bound, so beta > alpha indicates a game state that
// any sane opponent will never let happen.
//
// We also stop expanding nodes when depth reaches 0 or when the game is over.
bool Node::hasNextNode() const
{
	return depth > 0 && !isTerminalState() &&
			get<0>(nextNodeMove) <= 2 && get<1>(nextNodeMove) <= 2
			&& beta > alpha;
}

void Node::expandNextNode(stack<Node>& fringe)
{
	auto x = get<0>(nextNodeMove);
	auto y = get<1>(nextNodeMove);

	// Has this function call already expanded a node.
	// We need to keep track of this so that we can increment nextNodeMove
	// until it points to the next valid move.
	auto expanded = false;

	for (/* y */; y < 3; ++y)
	{
		for (/* first init x as stored value, then 0 */ ; x < 3; ++x)
		{
			if (state->isFree(x, y))
			{
				if (!expanded)
				{
					// Add child state to the fringe
					auto newBoard = make_unique<GameBoard>(*state);
					auto newMove = make_unique<Move>(x, y);
					newBoard->makeMove(*newMove);
					fringe.emplace(Node{move(newBoard), this,
						move(newMove), depth > 0 ? depth - 1 : 0,
						alpha, beta, !maximizer});
					expanded = true; // Only expand once per function call
				}
				else
				{
					// Save the coordinates of the next free space
					nextNodeMove = decltype(nextNodeMove){ x, y };
					return;
				}
			}
		}
		x = 0; // On a new row, so reset x to 0
	}

	// No more nodes found, so indicate that with an invalid move
	nextNodeMove = decltype(nextNodeMove){ 3, 3 };
}

Heuristic Node::getValue() const
{
	if (parent && ((depth == 0) || isTerminalState()))
	{
		return parent->state->getHeuristic(*action);
	}

	return maximizer ? alpha : beta;
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
		// the value of a maximizer node is the highest
		// value of any of its children. It stores this
		// value as its alpha.
		if (child.getValue() > alpha)
		{
			alpha = child.getValue();
			if (bestMove)
			{
				*bestMove = *child.action;
			}
			else
			{
				bestMove = make_unique<Move>(*child.action);
			}
		}
	}
	else
	{
		// The value of a minimizer node is the lowest
		// value of any of its children. It stores this
		// value as its beta.
		if (child.getValue() < beta)
		{
			beta = child.getValue();
			if (bestMove)
			{
				*bestMove = *child.action;
			}
			else
			{
				bestMove = make_unique<Move>(*child.action);
			}
		}
	}
}

bool Node::isTerminalState() const
{
	return state->endState() != ttt::EndState::NotOver;
}

Move Node::getBestMove() const
{
	assert(bestMove != nullptr);
	return *bestMove;
}

ostream& Node::print(ostream& stream) const
{
	stream << "Node{ State{ \""
			<< state->get(0,0) << state->get(1,0) << state->get(2,0) << "/"
			<< state->get(0,1) << state->get(1,1) << state->get(2,1) << "/"
			<< state->get(0,2) << state->get(1,2) << state->get(2,2)
			<< "\" }, Action=";
	if (action)
	{
		stream << *action;
	}
	else
	{
		stream << "null";
	}
	stream << ", BestMove=";
	if (bestMove)
	{
		stream << *bestMove;
	}
	else
	{
		stream << "null";
	}
	return stream << " }";
}

std::ostream& operator<<(std::ostream& stream, const Node& node)
{
	return node.print(stream);
}
