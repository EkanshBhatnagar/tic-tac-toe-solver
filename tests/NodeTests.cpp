#include <gtest/gtest.h>
#include <memory>
#include <queue>
#include "GameBoard.h"
#include "Move.h"
#include "Node.h"
using namespace std;

TEST(NodeTest, ZeroDepthHasNoNextNode)
{
	auto n = Node{
		unique_ptr<GameBoard>{new GameBoard{"   /   /   "}}, 0, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, FullBoardHasNoNextNode)
{
	auto n = Node{
		unique_ptr<GameBoard>{new GameBoard{"OXO/XXO/XOX"}}, 9, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, XWinningBoardHasNoNextNode)
{
	auto n = Node{
		unique_ptr<GameBoard>{new GameBoard{"XXX/OO /   "}}, 5, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, OWinningBoardHasNoNextNode)
{
	auto n = Node{
		unique_ptr<GameBoard>{new GameBoard{"XX /OOO/X  "}}, 4, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, EmptyBoardHasNextNode)
{
	auto n = Node{
		unique_ptr<GameBoard>{new GameBoard{"   /   /   "}}, 1, true};
	EXPECT_TRUE(n.hasNextNode());
}

TEST(NodeTest, UpdateParentOnRootDoesNotCrash)
{
	auto n = Node{
			unique_ptr<GameBoard>{new GameBoard{"   /   /   "}}, 1, true};
	n.updateParent(); // Has no parent, but still shouldn't segfault
	EXPECT_TRUE(true);
}

TEST(NodeTest, FirstExpansionAddsOneToFringe)
{
	auto n = Node{
			unique_ptr<GameBoard>{new GameBoard{"   /   /   "}}, 2, true};
	auto fringe = queue<Node>{};
	EXPECT_EQ(0, fringe.size());
	n.expandNextNode(fringe);
	EXPECT_EQ(1, fringe.size());
}

TEST(NodeTest, EmptyBoardRootNodeExpandsNineTimes)
{
	auto n = Node{
			unique_ptr<GameBoard>{new GameBoard{"   /   /   "}}, 2, true};
	auto fringe = queue<Node>{};
	EXPECT_EQ(0, fringe.size());
	for (auto i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(n.hasNextNode());
		n.expandNextNode(fringe);
		EXPECT_EQ(i + 1, fringe.size());
	}
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, DepthFirstExpansionBottomsOutWhenBoardFull)
{
	auto fringe = queue<Node>{};
	fringe.emplace(Node{
		unique_ptr<GameBoard>{new GameBoard{"   /   /   "}}, 9, true});
	for (auto i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(fringe.front().hasNextNode());
		fringe.front().expandNextNode(fringe);
	}
	EXPECT_FALSE(fringe.front().hasNextNode());
}

TEST(NodeTest, SubsequentNodesExpandRightNumberOfTimes)
{
	auto n = Node{
		unique_ptr<GameBoard>{new GameBoard{"  O/ XO/X X"}}, 9, true};
	auto counter = queue<Node>{};
	for (auto i = 0; i < 4; ++i)
	{
		EXPECT_TRUE(n.hasNextNode());
		n.expandNextNode(counter);
		EXPECT_EQ(i + 1, counter.size());
	}
	EXPECT_FALSE(n.hasNextNode());
}
