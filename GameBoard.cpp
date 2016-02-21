/*
 * GameBoard.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <assert.h>
#include <ostream>
#include <bitset>
#include "GameBoard.h"
#include <string>
#include "Move.h"
#include "Types.h"
#include "Heuristic.h"
using namespace std;

constexpr bitset<9> GameBoard::winStates[];

GameBoard::GameBoard() : xstate{0}, ostate{0}
{
}

// Board state string looks something like "XXX/OOO/   ",
// which would mean 3 Xs on the top row, 3 Os in the middle row,
// and the bottom row blank.
GameBoard::GameBoard(std::string boardState) : GameBoard()
{
	assert(boardState.size() == 11 || boardState.size() == 9);
	if (boardState.size() == 11)
	{
		boardState.erase(3, 1);
		boardState.erase(6, 1);
	}

	auto xbits = bitset<9>{};
	auto obits = bitset<9>{};
	for (auto i = 0; i < 9; ++i)
	{
		if (boardState[i] == 'X')
		{
			xbits[i] = 1;
		}
		else if (boardState[i] == 'O')
		{
			obits[i] = 1;
		}
	}

	xstate = xbits.to_ulong();
	ostate = obits.to_ulong();
}

GameBoard::GameBoard(bitset<9> xstate, bitset<9> ostate)
	: xstate{xstate}, ostate{ostate}
{
}

uint8_t GameBoard::usedSpaces() const
{
	return (xstate | ostate).count();
}

ttt::Player GameBoard::currentPlayer() const
{
	/* X always goes first, so if the number of filled spaces
	 * is even, it's X's turn, otherwise O's. */
	if ((xstate | ostate).count() % 2 == 0)
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
		if ((xstate & bitset<9>{pattern}) == pattern)
		{
			return ttt::EndState::XWin;
		}
		else if ((ostate & bitset<9>{pattern}) == pattern)
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
	if (xstate[x + y * 3])
	{
		return 'X';
	}
	else if (ostate[x + y * 3])
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

Heuristic GameBoard::getHeuristic(const Move& move) const
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
		auto xones = (xstate & pattern).count();
		auto oones = (ostate & pattern).count();
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
