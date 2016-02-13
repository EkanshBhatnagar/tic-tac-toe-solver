/*
 * GameBoard.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <iosfwd>
class Move;

class GameBoard final {
public:
	explicit GameBoard();
	~GameBoard();
	bool isFree(int x, int y) const;
	bool makeMove(const Move& playerMove);
	std::ostream& print(std::ostream& stream) const;
private:
	unsigned int xstate;
	unsigned int ostate;
	char get(int x, int y) const;
};

std::ostream& operator<< (std::ostream& stream, const GameBoard& board);

#endif /* GAMEBOARD_H_ */
