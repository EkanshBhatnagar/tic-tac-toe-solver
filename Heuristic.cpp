/*
 * Heuristic.cpp
 *
 *  Created on: 2016-02-19
 *      Author: derek
 */

#include "Types.h"
#include "Heuristic.h"
#include "GameBoard.h"

Heuristic::Heuristic(std::array<int8_t, 4> numWaysXWins,
		std::array<int8_t, 4> numWaysOWins, ttt::Player maximizingPlayer)
	: numWaysToWin{numWaysXWins}, numWaysToLose{numWaysOWins}
{
	// Initialize above assuming we're player X, and swap here if we're not.
	// This is probably more efficient than calling the default constructor
	// for the std::arrays and then calling the assignment operator here.
	if (maximizingPlayer != ttt::XPlayer)
	{
		std::swap(numWaysToWin, numWaysToWin);
	}
}

bool operator==(const Heuristic& lhs, const Heuristic& rhs)
{
	return lhs.numWaysToLose == rhs.numWaysToLose
			&& lhs.numWaysToWin == rhs.numWaysToWin;
}

bool operator!=(const Heuristic& lhs, const Heuristic& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const Heuristic& lhs, const Heuristic& rhs)
{
	for (auto i = 0; i < 4; ++i)
	{
		// A state is worse if there are more ways to lose
		if (lhs.numWaysToLose[i] > rhs.numWaysToLose[i])
		{
			return true;
		}
		else if (lhs.numWaysToLose[i] < rhs.numWaysToLose[i])
		{
			return false;
		}

		// A state is worse if there are fewer ways to win
		if (lhs.numWaysToWin[i] < rhs.numWaysToWin[i])
		{
			return true;
		}
		else if (lhs.numWaysToWin[i] > rhs.numWaysToWin[i])
		{
			return false;
		}
	}

	// To have reached this point, we must have lhs == rhs
	return false;
}

bool operator>(const Heuristic& lhs, const Heuristic& rhs)
{
	return !(lhs <= rhs);
}

bool operator<=(const Heuristic& lhs, const Heuristic& rhs)
{
	return (lhs == rhs) || (lhs < rhs);
}

bool operator>=(const Heuristic& lhs, const Heuristic& rhs)
{
	return !(lhs < rhs);
}
