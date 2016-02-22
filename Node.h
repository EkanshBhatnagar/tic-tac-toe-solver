/*
 * Node.h
 *
 *  Created on: 2016-02-13
 *      Author: derek
 */

#ifndef NODE_H_
#define NODE_H_

#include <iosfwd>
#include <memory>
#include <stack>
#include <cstdint>
#include "Heuristic.h"
class Move;
class GameBoard;

class Node {
public:
	explicit Node(const GameBoard& state, uint8_t depth, bool maximizer);
	explicit Node(std::string state, uint8_t depth, bool maximizer);
	Node(const Node&) = delete;
	Node& operator=(Node&) = delete;
	Node& operator=(Node&&) = default;
	Node(Node&&) = default;
	void expandNextNode(std::stack<Node>& fringe);
	bool hasNextNode() const;
	void updateParent();
	Move getBestMove() const;
	std::ostream& print(std::ostream& stream) const;
private: // Data members
	std::unique_ptr<GameBoard> state;
	Node* const parent;
	std::unique_ptr<Move> action; // action that got us here from the parent
	uint8_t depth;
	Heuristic alpha;
	Heuristic beta;
	bool maximizer; // TODO: See if you can eliminate the maximizer variable
	std::tuple<uint8_t, uint8_t> nextNodeMove;
	std::unique_ptr<Move> bestMove;
private: // Member functions
	explicit Node(std::unique_ptr<GameBoard> state, Node* const parent,
				std::unique_ptr<Move> action, uint8_t depth,
				Heuristic alpha, Heuristic beta, bool maximizer);
	void update(const Node& child);
	Heuristic getValue() const;
	bool isTerminalState() const;
};

std::ostream& operator<<(std::ostream& stream, const Node& node);

#endif /* NODE_H_ */
