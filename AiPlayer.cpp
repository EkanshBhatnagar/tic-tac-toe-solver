/*
 * AiPlayer.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include "AiPlayer.h"
#include "Move.h"
#include "GameBoard.h"

AiPlayer::AiPlayer(bool playerX) : Player{playerX}
{
}

AiPlayer::~AiPlayer()
{
}

Move AiPlayer::nextMove(const GameBoard& board)
{
}

