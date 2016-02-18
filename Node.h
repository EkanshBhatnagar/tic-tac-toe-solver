/*
 * Node.h
 *
 *  Created on: 2016-02-13
 *      Author: derek
 */

#ifndef NODE_H_
#define NODE_H_

#include <memory>
#include <list>
class Move;
class GameBoard;

class Node {
public:
	explicit Node(std::unique_ptr<GameBoard> state, const Node* parent,
			std::unique_ptr<Move> action, unsigned char depth, unsigned char cost);
private:
	std::list<Node> expand() const;
	std::unique_ptr<GameBoard> state;
	const Node* parent;
	std::unique_ptr<Move> action; // action that got us here from the parent
	unsigned char depth;
	unsigned char cost;
};

#endif /* NODE_H_ */
