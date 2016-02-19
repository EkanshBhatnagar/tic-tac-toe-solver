/*
 * AiPlayer.h
 *
 *  Created on: 2016-02-12
 *      Author: derek
 */

#ifndef AIPLAYER_H_
#define AIPLAYER_H_

#include "Player.h"
#include "Types.h"

class AiPlayer: public Player {
public:
	explicit AiPlayer(bool playerX);
	virtual ~AiPlayer();
	virtual Move nextMove(const GameBoard& board);
};

#endif /* AIPLAYER_H_ */
