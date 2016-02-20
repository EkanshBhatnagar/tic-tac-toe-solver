/*
 * GameBoard.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <assert.h>
#include <ostream>
#include "GameBoard.h"
#include "Move.h"
#include "Types.h"
#include "Heuristic.h"
using namespace std;

constexpr unsigned int GameBoard::winStates[];

// Helper functions for this file only
static uint8_t countOnes(unsigned int value);

GameBoard::GameBoard() : xstate{0}, ostate{0}
{
}

GameBoard::GameBoard(unsigned int xstate, unsigned int ostate)
	: xstate{xstate}, ostate{ostate}
{
}

uint8_t GameBoard::usedSpaces() const
{
	// Initially 9 empty spaces on the game board
	return 9 - countOnes(xstate | ostate);
}

ttt::Player GameBoard::currentPlayer() const
{
	/* X always goes first, so if the number of filled spaces
	 * is even, it's X's turn, otherwise O's. */
	if (countOnes(xstate | ostate) % 2 == 0)
	{
		return ttt::Player::XPlayer;
	}
	else
	{
		return ttt::Player::OPlayer;
	}
}

bool GameBoard::isFree(int x, int y) const {
	assert(x >= 0 && x <= 2 && y >= 0 && y <= 2);

	return (get(x, y) == ' ');
}

ttt::EndState GameBoard::endState() const
{
	for (auto pattern : winStates)
	{
		if ((xstate & pattern) == pattern)
		{
			return ttt::EndState::XWin;
		}
		else if ((ostate & pattern) == pattern)
		{
			return ttt::EndState::OWin;
		}
	}

	if ((xstate | ostate) == tieState)
	{
		return ttt::EndState::Tie;
	}

	return ttt::EndState::NotOver;
}

bool GameBoard::makeMove(const Move& playerMove) {
	if (!isFree(playerMove.x, playerMove.y))
	{
		return false;
	}

	if (currentPlayer() == ttt::Player::XPlayer)
	{
		xstate |= (1 << (playerMove.x + playerMove.y * 3));
	}
	else
	{
		ostate |= (1 << (playerMove.x + playerMove.y * 3));
	}

	return true;
}

char GameBoard::get(int x, int y) const
{
	if (xstate & (1 << (x + y * 3)))
	{
		return 'X';
	}
	else if (ostate & (1 << (x + y * 3)))
	{
		return 'O';
	}
	else
	{
		return ' ';
	}
}

ostream& GameBoard::print(ostream& stream) const
{
	return stream
				<< " " << get(0, 0) << " | " << get(1, 0) << " | " << get(2, 0)
				<< endl << "-----------" << endl
				<< " " << get(0, 1) << " | " << get(1, 1) << " | " << get(2, 1)
				<< endl << "-----------" << endl
				<< " " << get(0, 2) << " | " << get(1, 2) << " | " << get(2, 2)
                << endl;
}

Heuristic GameBoard::getHeuristic(ttt::Player forPlayer) const
{
	// Number of ways for X or O to win in 0 moves, 1 move, etc.
	uint8_t numWaysXWins[] = { 0, 0, 0, 0 };
	uint8_t numWaysOWins[] = { 0, 0, 0, 0 };
	ttt::Player player = currentPlayer();

	for (auto pattern : winStates)
	{
		// There are 8 ways to win Tic Tac Toe, and a pattern
		// representing each of them.
		//
		// As an example of the logic here, suppose we're looking at
		// the pattern corresponding to having every square on the top row,
		// and X currently has two squares in the top row, with one free.
		//
		// xstate & pattern: 110
		//
		// The result has 2 1's in it.
		// 3 - 2 = 1 more X needed in that row to win.
		// So we increment the number of ways for X to win in 1 move.
		//
		// It should also be clear that if the O player has even
		// a single square in that row, X will be unable to win
		// by claiming that row. The case when the O player
		// has no square in that row corresponds to
		//
		// ostate & pattern: 000
		auto xones = countOnes(xstate & pattern);
		auto oones = countOnes(ostate & pattern);
		if (oones == 0)
		{
			++numWaysXWins[3 - xones];
		}
		if (xones == 0)
		{
			++numWaysOWins[3 - oones];
		}
	}
}

// Non-member functions
ostream& operator<< (ostream& stream, const GameBoard& board)
{
	return board.print(stream);
}

// Static, non-member helper functions for this file only
uint8_t countOnes(unsigned int value)
{
	auto count = 0;
	for (size_t i = 0; i < sizeof(value) * 8; ++i)
	{
		if ((value & 1) == 1)
		{
			++count;
		}
		value >>= 1;
	}
	return count;
}
