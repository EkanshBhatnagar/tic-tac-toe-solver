#include <memory>
#include "Game.h"
#include "Player.h"
#include "AiPlayer.h"
#include "Node.h"
#include "Move.h"
#include "HumanPlayer.h"
#include "GameBoard.h"
using namespace std;

int main(int argc, char** argv)
{
    Game game{make_unique<AiPlayer>(true),
    	make_unique<HumanPlayer>(false)};
    game.run();

    return 0;
}
