/*
 * HumanPlayer.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <iostream>
#include <sstream>
#include "HumanPlayer.h"
#include "Move.h"
#include "GameBoard.h"
using namespace std;

HumanPlayer::HumanPlayer(bool playerX) : Player{playerX}
{
}

HumanPlayer::~HumanPlayer()
{
}

Move HumanPlayer::nextMove(const GameBoard& board)
{
	string input;
	int x = -1;
	int y = -1;
	bool validMove = false;

	// Display current board state
	cout.clear();
	cout << board;
	cout << "You are player " << (playerX ? "X" : "O") << endl;
	cout << "It is your turn" << endl;

	// Get user input
	while (!validMove)
	{
		cout << "Enter column (0-2): ";
		getline(cin, input);
		stringstream(input) >> x;
		cout << "Enter row (0-2): ";
		getline(cin, input);
		stringstream(input) >> y;

		// Check for errors
		if (x < 0 || x > 2 || y < 0 || y > 2)
		{
			cout << "Numbers must be between 0 and 2" << endl;
		}
		else if (!board.isFree(x, y))
		{
			cout << "That space is not free" << endl;
		}
		else
		{
			validMove = true;
		}
	}

	// Return move
	return Move(x, y, playerX);
}
