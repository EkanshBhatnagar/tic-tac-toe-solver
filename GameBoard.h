/*
 * GameBoard.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <iosfwd>
#include <list>
#include <cstdint>
#include "Types.h"
class Heuristic;
class Move;

class GameBoard final {
public:
	explicit GameBoard();
	explicit GameBoard(std::string boardState);
	bool isFree(int x, int y) const;
	uint8_t usedSpaces() const;
	bool makeMove(const Move& playerMove);
	std::ostream& print(std::ostream& stream) const;
	char get(int x, int y) const;
	ttt::EndState endState() const;
	ttt::Player currentPlayer() const;
	Heuristic getHeuristic(const Move& move) const;
private:
	uint16_t xstate;
	uint16_t ostate;
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
	static const unsigned int tieState = 511; // 111 111 111
	explicit GameBoard(unsigned int xstate, unsigned int ostate);
};

std::ostream& operator<< (std::ostream& stream, const GameBoard& board);

#endif /* GAMEBOARD_H_ */
