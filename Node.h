/*
 * Node.h
 *
 *  Created on: 2016-02-13
 *      Author: derek
 */

#ifndef NODE_H_
#define NODE_H_

#include <memory>
#include <queue>
#include <cstdint>
class Move;
class GameBoard;

class Node {
public:
	explicit Node(std::unique_ptr<GameBoard> state, uint8_t depth, bool maximizer);
	Node(const Node&) = delete;
	Node& operator=(Node&) = delete;
	Node& operator=(Node&&) = default;
	Node(Node&&) = default;
	void expandNextNode(std::queue<Node>& fringe);
	bool hasNextNode() const;
	bool isTerminalState() const;
	uint8_t getDepth() const;
	void updateParent();
	Move getBestMove() const;
private: // Data members
	std::unique_ptr<GameBoard> state;
	Node* const parent;
	std::unique_ptr<Move> action; // action that got us here from the parent
	uint8_t depth;
	int8_t alpha;
	int8_t beta;
	bool maximizer;
	int8_t bestChildValue;
	std::tuple<uint8_t, uint8_t> nextNodeMove;
	const Node* bestChild;
private: // Member functions
	explicit Node(std::unique_ptr<GameBoard> state, Node* const parent,
				std::unique_ptr<Move> action, uint8_t depth,
				int8_t alpha, int8_t beta, bool maximizer);
	void update(const Node& child);
	uint8_t getValue() const;
	uint8_t getHeuristic() const;
};

#endif /* NODE_H_ */
