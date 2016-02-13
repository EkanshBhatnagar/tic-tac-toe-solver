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

GameBoard::GameBoard() {
	for (int i = 0; i < 9; ++i)
	{
		state[i] = ' ';
	}
}

GameBoard::~GameBoard() {
	// TODO Auto-generated destructor stub
}

bool GameBoard::isFree(int x, int y) const {
	assert(x >= 0 && x <= 2 && y >= 0 && y <= 2);

	return state[x + y * 3] == ' ';
}

bool GameBoard::makeMove(const Move& playerMove) {
	if (!isFree(playerMove.x, playerMove.y))
	{
		return false;
	}

	state[playerMove.x + playerMove.y * 3] = playerMove.playerX ? 'X' : 'O';
	return true;
}

ostream& GameBoard::print(ostream& stream) const
{
	return stream
				<< " " << state[0] << " | " << state[1] << " | " << state[2]
				<< endl << "-----------" << endl
				<< " " << state[3] << " | " << state[4] << " | " << state[5]
				<< endl << "-----------" << endl
				<< " " << state[6] << " | " << state[7] << " | " << state[8]
                << endl;
}

ostream& operator<< (ostream& stream, const GameBoard& board)
{
	return board.print(stream);
}
