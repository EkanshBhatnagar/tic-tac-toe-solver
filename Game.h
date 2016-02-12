#ifndef GAME_H_
#define GAME_H_

#include <memory>
class GameBoard;
class Player;

class Game
{
public:
    Game(std::unique_ptr<Player> playerX, std::unique_ptr<Player> playerO);
    void run();
private:
    std::unique_ptr<GameBoard> m_board;
    std::unique_ptr<Player> m_playerX;
    std::unique_ptr<Player> m_playerO;
    bool isOver;
    bool xTurn;
};

#endif /* GAME_H_ */
