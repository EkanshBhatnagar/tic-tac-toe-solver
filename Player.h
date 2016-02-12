#ifndef PLAYER_H_
#define PLAYER_H_

class GameBoard;
class Move;

class Player
{
public:
	Player();
	virtual ~Player();
    virtual Move nextMove(const GameBoard& board)=0;
};

#endif /* PLAYER_H_ */
