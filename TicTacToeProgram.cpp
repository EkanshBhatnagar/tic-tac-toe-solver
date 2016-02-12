#include <iostream>
#include <memory>
#include "Game.h"
#include "Player.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
#include "GameBoard.h"
using namespace std;

int main(int argc, char** argv)
{
    unique_ptr<Player> human{new HumanPlayer};
    unique_ptr<Player> ai{new AiPlayer};
    unique_ptr<Game> game{new Game{std::move(human), std::move(ai)}};

    //while (!game.isOver())
    //{
    //}

    return 0;
}
