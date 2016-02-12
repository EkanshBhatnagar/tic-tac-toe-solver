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
	assert(x > 0 && x <= 2 && y > 0 && y <= 2);

	return state[x + y * 3] == ' ';
}

bool GameBoard::makeMove(const Move& playerMove) {


	if (!isFree(playerMove.x, playerMove.y))
	{
		return false;
	}

	state[playerMove.x + playerMove.y * 3] = playerMove.playerX ? 'X' : 'Y';
	return true;
}

ostream& operator<< (ostream& stream, const GameBoard& board)
{
	return stream
			<< " " << board.state[0] << " | " << board.state[1] << " | " << board.state[2] << endl
			<< "-----------" << endl
			<< " " << board.state[3] << " | " << board.state[4] << " | " << board.state[5] << endl
			<< "-----------" << endl
			<< " " << board.state[6] << " | " << board.state[7] << " | " << board.state[8] << endl;
}
