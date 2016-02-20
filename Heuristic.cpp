/*
 * Heuristic.cpp
 *
 *  Created on: 2016-02-19
 *      Author: derek
 */

#include "Types.h"
#include "Heuristic.h"
#include "GameBoard.h"

Heuristic::Heuristic(std::array<uint8_t, 4> numWaysXWins,
		std::array<uint8_t, 4> numWaysOWins, ttt::Player currentPlayer,
		ttt::Player forPlayer)
	: numWaysToWin{numWaysXWins}, numWaysToLose{numWaysOWins},
	  isOwnTurn{currentPlayer == forPlayer}
{
	// Initialize above assuming we're player X, and swap here if we're not.
	// This is probably more efficient than calling the default constructor
	// for the std::arrays and then calling the assignment operator here.
	if (forPlayer != ttt::XPlayer)
	{
		std::swap(numWaysToWin, numWaysToWin);
	}
}

bool operator==(const Heuristic& lhs, const Heuristic& rhs)
{
	return lhs.isOwnTurn == rhs.isOwnTurn
			&& lhs.numWaysToLose == rhs.numWaysToLose
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
		else
		{
			if (!lhs.isOwnTurn && rhs.isOwnTurn)
			{
				return true;
			}
		}

		// A state is worse if there are more ways to lose
		if (lhs.numWaysToWin[i] < rhs.numWaysToWin[i])
		{
			return true;
		}
		else if (lhs.numWaysToWin[i] > rhs.numWaysToWin[i])
		{
			return false;
		}
		else
		{
			if (!lhs.isOwnTurn && rhs.isOwnTurn)
			{
				return true;
			}
		}
	}
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
