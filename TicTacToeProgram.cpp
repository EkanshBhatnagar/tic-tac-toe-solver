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
    unique_ptr<Player> human1{new HumanPlayer{true}};
    unique_ptr<Player> human2{new HumanPlayer{false}};
    //unique_ptr<Player> ai{new AiPlayer{false}};
    Game game{std::move(human1), std::move(human2)};

    game.run();

    return 0;
}
