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
	static constexpr unsigned int winStates[] =
	{
			// Full rows
			1 << 0 | 1 << 1 | 1 << 2, // 111 *** ***
			1 << 3 | 1 << 4 | 1 << 5, // *** 111 ***
			1 << 6 | 1 << 7 | 1 << 8, // *** *** 111
			// Full columns
			1 << 0 | 1 << 3 | 1 << 6, // 1** 1** 1**
			1 << 1 | 1 << 4 | 1 << 7, // *1* *1* *1*
			1 << 2 | 1 << 5 | 1 << 8, // **1 **1 **1
			// Diagonals
			1 << 0 | 1 << 4 | 1 << 8, // 1** *1* **1
			1 << 2 | 1 << 4 | 1 << 6  // **1 *1* 1**
	};
	char get(int x, int y) const;
};

std::ostream& operator<< (std::ostream& stream, const GameBoard& board);

#endif /* GAMEBOARD_H_ */
