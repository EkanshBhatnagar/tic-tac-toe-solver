#include <gtest/gtest.h>
#include "GameBoard.h"
#include "Heuristic.h"
#include "Types.h"
#include "Move.h"

TEST(HeuristicTest, Default)
{
	auto gb = GameBoard{"   /   /  X"};
	EXPECT_LT(gb.getHeuristic(Move{2,0}), gb.getHeuristic(Move{1,1}));
}
