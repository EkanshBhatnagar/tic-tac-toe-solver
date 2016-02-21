#include <gtest/gtest.h>
#include "GameBoard.h"
#include "Heuristic.h"
#include "Types.h"
#include "Move.h"

TEST(HeuristicTest, BestFirstMoveXInCenter)
{
	auto gb = GameBoard{"   /   /   "};
	EXPECT_LT(gb.getHeuristic(Move{0,0}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{1,0}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{2,0}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{0,1}), gb.getHeuristic(Move{1,1}));
	EXPECT_EQ(gb.getHeuristic(Move{1,1}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{2,1}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{0,2}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{1,2}), gb.getHeuristic(Move{1,1}));
	EXPECT_LT(gb.getHeuristic(Move{2,2}), gb.getHeuristic(Move{1,1}));
}

TEST(HeuristicTest, BetterMinimizingMovesHaveSmallerValues)
{
	auto gb = GameBoard{"   / X /   "};
	// Because this is the second move, it's OPlayer's turn, and
	// X is the maximizing player. Hence the better move has the
	// smaller value.
	EXPECT_LT(gb.getHeuristic(Move{0,0}), gb.getHeuristic(Move{1,0}));
}

TEST(HeuristicTest, SymmetricBoardStatesAreEquivalent)
{
	auto gb = GameBoard{"   / X /   "};
	// Corners
	EXPECT_EQ(gb.getHeuristic(Move{0,0}), gb.getHeuristic(Move{2,2}));
	EXPECT_EQ(gb.getHeuristic(Move{2,0}), gb.getHeuristic(Move{2,2}));
	EXPECT_EQ(gb.getHeuristic(Move{0,2}), gb.getHeuristic(Move{2,2}));
	// Sides
	EXPECT_EQ(gb.getHeuristic(Move{1,2}), gb.getHeuristic(Move{1,0}));
	EXPECT_EQ(gb.getHeuristic(Move{2,1}), gb.getHeuristic(Move{1,0}));
	EXPECT_EQ(gb.getHeuristic(Move{0,1}), gb.getHeuristic(Move{1,0}));
}
