/*
 * Heuristic.h
 *
 *  Created on: 2016-02-19
 *      Author: derek
 */

#ifndef HEURISTIC_H_
#define HEURISTIC_H_

class GameBoard;
#include "Types.h"
#include <cstdint>
#include <array>

class Heuristic {
public:
	Heuristic(std::array<uint8_t, 4> numWaysXWins,
			std::array<uint8_t, 4> numWaysOWins,
			ttt::Player currentPlayer, ttt::Player forPlayer);
	friend bool operator==(const Heuristic& lhs, const Heuristic& rhs);
	friend bool operator<(const Heuristic& lhs, const Heuristic& rhs);
private:
	std::array<uint8_t, 4> numWaysToWin;
	std::array<uint8_t, 4> numWaysToLose;
	bool isOwnTurn;
};

bool operator==(const Heuristic& lhs, const Heuristic& rhs);
bool operator!=(const Heuristic& lhs, const Heuristic& rhs);
bool operator<(const Heuristic& lhs, const Heuristic& rhs);
bool operator>(const Heuristic& lhs, const Heuristic& rhs);
bool operator<=(const Heuristic& lhs, const Heuristic& rhs);
bool operator>=(const Heuristic& lhs, const Heuristic& rhs);

#endif /* HEURISTIC_H_ */
