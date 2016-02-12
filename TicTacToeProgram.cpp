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
    Game game{std::move(human), std::move(ai)};

    game.run();

    return 0;
}
