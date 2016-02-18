/*
 * Node.cpp
 *
 *  Created on: 2016-02-13
 *      Author: derek
 */

#include "Node.h"
#include "Move.h"
#include "GameBoard.h"
#include <list>
#include <memory>
using namespace std;

Node::Node(std::unique_ptr<GameBoard> state, const Node* parent,
		std::unique_ptr<Move> action, unsigned char depth,
		unsigned char cost)
	: state{std::move(state)}, parent{parent}, action{std::move(action)},
	  depth{depth}, cost{cost}
{

}

list<Node> Node::expand() const
{
	auto newNodes = list<Node>{};

	for (auto x = 0; x < 3; ++x)
	{
		for (auto y = 0; y < 3; ++y)
		{
			if (state->get(x, y) == ' ')
			{
				auto newBoard = unique_ptr<GameBoard>{new GameBoard{*state}};
				auto newMove = unique_ptr<Move>{new Move{x, y}};
				newBoard->makeMove(*newMove);
				auto newNode = Node{std::move(newBoard), this, std::move(newMove), depth + 1, cost + 1};
				newNodes.push_back(std::move(newNode));
			}
		}
	}

	return newNodes;
}
