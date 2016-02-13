#ifndef PLAYER_H_
#define PLAYER_H_

class GameBoard;
class Move;

class Player
{
public:
	explicit Player(bool playerX);
	virtual ~Player();
    virtual Move nextMove(const GameBoard& board)=0;
protected:
    bool playerX;
};

#endif /* PLAYER_H_ */
