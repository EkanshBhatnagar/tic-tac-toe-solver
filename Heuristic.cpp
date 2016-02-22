/*
 * Heuristic.cpp
 *
 *  Created on: 2016-02-19
 *      Author: derek
 */

#include <ostream>
#include <iterator>
#include "Types.h"
#include "Heuristic.h"
#include "GameBoard.h"
using namespace std;

Heuristic::Heuristic(array<int8_t, 4> numWaysXWins,
		array<int8_t, 4> numWaysOWins, ttt::Player maximizingPlayer)
	: numWaysToWin{numWaysXWins}, numWaysToLose{numWaysOWins}
{
	// Initialize above assuming we're player X, and swap here if we're not.
	// This is probably more efficient than calling the default constructor
	// for the std::arrays and then calling the assignment operator here.
	if (maximizingPlayer != ttt::XPlayer)
	{
		swap(numWaysToWin, numWaysToWin);
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

const Heuristic& Heuristic::max()
{
	// Don't worry about leaking memory, since the static object
	// is meant to live till the end of the program, when the OS
	// cleans everything up anyway.
	static const Heuristic* max = new Heuristic{{4,4,4,4}, {-4,-4,-4,-4}};
	return *max;
}

const Heuristic& Heuristic::min()
{
	// Don't worry about leaking memory, since the static object
	// is meant to live till the end of the program, when the OS
	// cleans everything up anyway.
	static const Heuristic* min = new Heuristic{{-4,-4,-4,-4}, {4,4,4,4}};
	return *min;
}

ostream& Heuristic::print(ostream& stream) const
{
	stream << "Heuristic{ WaysToWin{ ";
	copy(begin(numWaysToWin), end(numWaysToWin),
			ostream_iterator<int>(stream, ","));
	stream << "}, WaysToLose{ ";
	copy(begin(numWaysToLose), end(numWaysToLose),
			ostream_iterator<int>(stream, ","));
	stream << "} }";
	return stream;
}

ostream& operator<< (ostream& stream, const Heuristic& h)
{
	return h.print(stream);
}

