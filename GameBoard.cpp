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
using namespace std;

GameBoard::GameBoard() : xstate(0), ostate(0)
{
}

GameBoard::~GameBoard() {
	// TODO Auto-generated destructor stub
}

bool GameBoard::isFree(int x, int y) const {
	assert(x >= 0 && x <= 2 && y >= 0 && y <= 2);

	return (get(x, y) == ' ');
}

bool GameBoard::makeMove(const Move& playerMove) {
	if (!isFree(playerMove.x, playerMove.y))
	{
		return false;
	}

	if (playerMove.playerX)
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
				<< " " << get(0, 0) << " | " << get(0, 1) << " | " << get(0, 2)
				<< endl << "-----------" << endl
				<< " " << get(1, 0) << " | " << get(1, 1) << " | " << get(1, 2)
				<< endl << "-----------" << endl
				<< " " << get(2, 0) << " | " << get(2, 1) << " | " << get(2, 2)
                << endl;
}

ostream& operator<< (ostream& stream, const GameBoard& board)
{
	return board.print(stream);
}
