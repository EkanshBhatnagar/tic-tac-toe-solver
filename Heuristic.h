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
#include <iosfwd>

class Heuristic {
public:
	Heuristic(std::array<int8_t, 4> numWaysXWins,
			std::array<int8_t, 4> numWaysOWins,
			ttt::Player maximizingPlayer = ttt::Player::XPlayer);
	friend bool operator==(const Heuristic& lhs, const Heuristic& rhs);
	friend bool operator<(const Heuristic& lhs, const Heuristic& rhs);
	std::ostream& print(std::ostream& stream) const;
	static const Heuristic& max();
	static const Heuristic& min();

private:
	std::array<int8_t, 4> numWaysToWin;
	std::array<int8_t, 4> numWaysToLose;
};

bool operator==(const Heuristic& lhs, const Heuristic& rhs);
bool operator!=(const Heuristic& lhs, const Heuristic& rhs);
bool operator<(const Heuristic& lhs, const Heuristic& rhs);
bool operator>(const Heuristic& lhs, const Heuristic& rhs);
bool operator<=(const Heuristic& lhs, const Heuristic& rhs);
bool operator>=(const Heuristic& lhs, const Heuristic& rhs);

std::ostream& operator<< (std::ostream& stream, const Heuristic& h);

#endif /* HEURISTIC_H_ */
