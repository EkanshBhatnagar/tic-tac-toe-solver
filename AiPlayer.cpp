/*
 * AiPlayer.cpp
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#include <list>
#include "AiPlayer.h"
#include "Move.h"
#include "GameBoard.h"
#include "Node.h"
using namespace std;

static list<GameBoard> successorStates(const GameBoard& board);
static list<Node> expand(const Node& node);

AiPlayer::AiPlayer(bool playerX) : Player{playerX}
{
}

AiPlayer::~AiPlayer()
{
}

Move AiPlayer::nextMove(const GameBoard& board)
{

}




