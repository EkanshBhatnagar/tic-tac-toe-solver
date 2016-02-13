#include <memory>
#include <iostream>
#include "Game.h"
#include "GameBoard.h"
#include "Player.h"
#include "Move.h"
using namespace std;

Game::Game(std::unique_ptr<Player> playerX, std::unique_ptr<Player> playerO)
    : m_board{new GameBoard}, m_playerX{move(playerX)}, m_playerO{move(playerO)},
    isOver{false}, xTurn{true}
{
  
}

void Game::run()
{
    auto currentPlayer = m_playerX.get();

    while (m_board->endState() == ttt::EndState::NotOver)
    {
        // Let the current player make their move
        m_board->makeMove((currentPlayer->nextMove(*m_board.get())));

        // Next player's turn
        currentPlayer = currentPlayer == m_playerX.get() ? m_playerO.get() : m_playerX.get();
    }

    // Game is over, display final state
    cout << "Final game state:" << endl << *m_board.get();

    // Display victory or defeat message
    switch (m_board->endState())
    {
    case ttt::EndState::XWin:
    	cout << "Player X wins!" << endl;
    	break;
    case ttt::EndState::OWin:
    	cout << "Player O wins!" << endl;
    	break;
    default:
    	cout << "Game ended in a tie" << endl;
    }
}
