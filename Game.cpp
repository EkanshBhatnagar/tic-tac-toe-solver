#include <memory>
#include "Game.h"
#include "GameBoard.h"
#include "Player.h"
using namespace std;

Game::Game(std::unique_ptr<Player> playerX, std::unique_ptr<Player> playerO)
    : m_board{new GameBoard}, m_playerX{move(playerX)}, m_playerO{move(playerO)},
    isOver{false}, xTurn{true}
{
  
}

void Game::run()
{
    auto currentPlayer = m_playerX.get();

    while (!isOver)
    {
        // Let the current player make their move
        //applyMove(currentPlayer->move(m_board.get()));

        // Check if anyone won
        //updateGameOver();

        // Next player's turn
        currentPlayer = currentPlayer == m_playerX.get() ? m_playerO.get() : m_playerX.get();
    } 
}
