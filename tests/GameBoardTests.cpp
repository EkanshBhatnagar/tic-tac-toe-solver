#include <gtest/gtest.h>
#include "GameBoard.h"
#include "Types.h"
#include "Move.h"

/*
	explicit GameBoard();
	explicit GameBoard(std::string boardState);
	bool isFree(int x, int y) const;
	uint8_t usedSpaces() const;
	bool makeMove(const Move& playerMove);
	ttt::Player currentPlayer() const;
	Heuristic getHeuristic(const Move& move) const;
*/

TEST(GameBoardTest, XGoesFirst)
{
	auto gb = GameBoard{};
	EXPECT_EQ(gb.currentPlayer(), ttt::Player::XPlayer);
}

TEST(GameBoardTest, DefaultBoardIsEmpty)
{
	auto gb = GameBoard{};
	for (auto i = 0; i < 2; ++i)
	{
		for (auto j = 0; j < 2; ++j)
		{
			EXPECT_EQ(' ', gb.get(i, j));
			EXPECT_TRUE(gb.isFree(i, j));
		}
	}
}


TEST(GameBoardTest, TurnsAlternate)
{
	auto gb = GameBoard{};
	auto p1 = gb.currentPlayer();
	gb.makeMove(Move{1,1});
	EXPECT_NE(p1, gb.currentPlayer());
	gb.makeMove(Move{1,2});
	EXPECT_EQ(p1, gb.currentPlayer());
}

TEST(GameBoardTest, MakeMove)
{
	auto gb = GameBoard{};
	gb.makeMove(Move{0,1});
	EXPECT_EQ('X', gb.get(0,1));
	gb.makeMove(Move{1,1});
	EXPECT_EQ('O', gb.get(1,1));
}

TEST(GameBoardTest, UsedSpaces)
{
	auto gb = GameBoard{};
	EXPECT_EQ(0, gb.usedSpaces());
	gb.makeMove(Move{0,1});
	EXPECT_EQ(1, gb.usedSpaces());
	gb.makeMove(Move{1,1});
	EXPECT_EQ(2, gb.usedSpaces());
}

TEST(GameBoardTest, Getters)
{
	auto gb = GameBoard{"O  /  X/   "};
	EXPECT_EQ('O', gb.get(0,0));
	EXPECT_EQ(' ', gb.get(1,0));
	EXPECT_EQ(' ', gb.get(2,0));
	EXPECT_EQ(' ', gb.get(0,1));
	EXPECT_EQ(' ', gb.get(1,1));
	EXPECT_EQ('X', gb.get(2,1));
	EXPECT_EQ(' ', gb.get(0,2));
	EXPECT_EQ(' ', gb.get(1,2));
	EXPECT_EQ(' ', gb.get(2,2));
}

TEST(GameBoardTest, IsFree)
{
	auto gb = GameBoard{"O  /  X/   "};
	EXPECT_FALSE(gb.isFree(0,0));
	EXPECT_TRUE(gb.isFree(1,0));
	EXPECT_TRUE(gb.isFree(2,0));
	EXPECT_TRUE(gb.isFree(0,1));
	EXPECT_TRUE(gb.isFree(1,1));
	EXPECT_FALSE(gb.isFree(2,1));
	EXPECT_TRUE(gb.isFree(0,2));
	EXPECT_TRUE(gb.isFree(1,2));
	EXPECT_TRUE(gb.isFree(2,2));
}

TEST(GameBoardTest, EndState)
{
	EXPECT_EQ(ttt::EndState::XWin, GameBoard{"XXX/OO /   "}.endState());
	EXPECT_EQ(ttt::EndState::OWin, GameBoard{"XX /OOO/X  "}.endState());
	EXPECT_EQ(ttt::EndState::NotOver, GameBoard{"   / X /   "}.endState());
	EXPECT_EQ(ttt::EndState::Tie, GameBoard{"OXO/XXO/XOX"}.endState());
}
