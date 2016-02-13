/*
 * HumanPlayer.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"
class GameBoard;

class HumanPlayer: public Player {
public:
	explicit HumanPlayer(bool playerX);
	virtual ~HumanPlayer();
	virtual Move nextMove(const GameBoard& board);
};

#endif /* HUMANPLAYER_H_ */
