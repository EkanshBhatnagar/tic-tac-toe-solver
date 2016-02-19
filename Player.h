#ifndef PLAYER_H_
#define PLAYER_H_

#include "Types.h"
class GameBoard;
class Move;

class Player
{
public:
	explicit Player(bool playerX);
	virtual ~Player();
    virtual Move nextMove(const GameBoard& board)=0;
protected:
    ttt::Player player;
};

#endif /* PLAYER_H_ */
