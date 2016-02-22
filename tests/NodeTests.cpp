#include <gtest/gtest.h>
#include <memory>
#include <queue>
#include <stack>
#include "GameBoard.h"
#include "Move.h"
#include "Node.h"
using namespace std;

TEST(NodeTest, ZeroDepthHasNoNextNode)
{
	auto n = Node{"   /   /   ", 0, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, FullBoardHasNoNextNode)
{
	auto n = Node{"OXO/XXO/XOX", 9, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, XWinningBoardHasNoNextNode)
{
	auto n = Node{"XXX/OO /   ", 5, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, OWinningBoardHasNoNextNode)
{
	auto n = Node{"XX /OOO/X  ", 4, true};
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, EmptyBoardHasNextNode)
{
	auto n = Node{"   /   /   ", 1, true};
	EXPECT_TRUE(n.hasNextNode());
}

TEST(NodeTest, UpdateParentOnRootDoesNotCrash)
{
	auto n = Node{"   /   /   ", 1, true};
	n.updateParent(); // Has no parent, but still shouldn't segfault
	EXPECT_TRUE(true);
}

TEST(NodeTest, FirstExpansionAddsOneToFringe)
{
	auto n = Node{"   /   /   ", 2, true};
	auto fringe = stack<Node>{};
	EXPECT_EQ(0, fringe.size());
	n.expandNextNode(fringe);
	EXPECT_EQ(1, fringe.size());
}

TEST(NodeTest, EmptyBoardRootNodeExpandsNineTimes)
{
	auto n = Node{"   /   /   ", 2, true};
	auto fringe = stack<Node>{};
	EXPECT_EQ(0, fringe.size());
	for (auto i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(n.hasNextNode());
		n.expandNextNode(fringe);
		EXPECT_EQ(i + 1, fringe.size());
	}
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, DepthFirstExpansionStopsOnWinState)
{
	auto fringe = stack<Node>{};
	fringe.emplace(Node{"   /   /   ", 9, true});
	for (auto i = 0; i < 7; ++i)
	{
		EXPECT_TRUE(fringe.top().hasNextNode());
		fringe.top().expandNextNode(fringe);
	}
	// When doing a depth first search of board states, we should
	// end up with "XOX/OXO/X  "  after 7 moves, which is a win
	// along the diagonal for X.
	EXPECT_FALSE(fringe.top().hasNextNode());
}

TEST(NodeTest, DepthFirstExpansionStopsOnFullBoard)
{
	auto fringe = stack<Node>{};
	fringe.emplace(Node{"  O/O X/XXO", 9, true});

	// Move to "X O/O X/XXO"
	EXPECT_TRUE(fringe.top().hasNextNode());
	fringe.top().expandNextNode(fringe);

	// Move to "XOO/O X/XXO"
	EXPECT_TRUE(fringe.top().hasNextNode());
	fringe.top().expandNextNode(fringe);

	// Move to "XOO/OXX/XXO"
	EXPECT_TRUE(fringe.top().hasNextNode());
	fringe.top().expandNextNode(fringe);

	EXPECT_FALSE(fringe.top().hasNextNode());
}

// Tests bug fixed in commit 130ad96da30843fe23a8df806cc2833d81b3ef81
TEST(NodeTest, MoveIterationDoesNotSkipNodes)
{
	auto n = Node{"  O/ XO/X X", 9, false};
	auto counter = stack<Node>{};
	for (auto i = 0; i < 4; ++i)
	{
		EXPECT_TRUE(n.hasNextNode());
		n.expandNextNode(counter);
		EXPECT_EQ(i + 1, counter.size());
	}
}

// Tests bug fixed in commit cd5ffd0d1378d5a883ad46d44a091dfefa181351
TEST(NodeTest, NonEmptyNodesExpandRightNumberOfTimes)
{
	auto n = Node{"  O/ XO/X X", 9, false};
	auto counter = stack<Node>{};
	for (auto i = 0; i < 4; ++i)
	{
		n.expandNextNode(counter);
	}
	EXPECT_EQ(4, counter.size());
	EXPECT_FALSE(n.hasNextNode());
}

TEST(NodeTest, FirstExpandedNodeUpdatesParent)
{
	auto n = Node{"   /   /   ", 1, true};
	auto fringe = stack<Node>{};

	// Expand first node
	n.expandNextNode(fringe);
	fringe.top().updateParent();

	// Expected best move
	auto m = Move{0,0};
	EXPECT_EQ(m, n.getBestMove());
}

// Finds the best first move for the X player
TEST(NodeTest, FindBestMaximizingMoveFromEmptyBoard)
{
	auto n = Node{"   /   /   ", 1, true};
	auto fringe = stack<Node>{};

	while (n.hasNextNode())
	{
		n.expandNextNode(fringe);
		fringe.top().updateParent();
	}

	auto m = Move{1,1};
	EXPECT_EQ(m, n.getBestMove());
}

// This one finds the best first move for the O player
TEST(NodeTest, FindBestMinimizingMoveAfterOneX)
{
	auto n = Node{"   / X /   ", 1, false};
	auto fringe = stack<Node>{};

	while (n.hasNextNode())
	{
		n.expandNextNode(fringe);
		fringe.top().updateParent();
	}

	auto m = Move{0,0};
	EXPECT_EQ(m, n.getBestMove());
}

// Finds the best second move for the X player
TEST(NodeTest, FindBestMoveAfterOneO)
{
	auto n = Node{"O  / X /   ", 1, true};
	auto fringe = stack<Node>{};

	while (n.hasNextNode())
	{
		n.expandNextNode(fringe);
		fringe.top().updateParent();
	}

	auto m = Move{2,0};
	EXPECT_EQ(m, n.getBestMove());
}

// Finds the best move for the X player
TEST(NodeTest, FindBestMovesAtDepth2)
{
	auto fringe = stack<Node>{};
	fringe.emplace(Node{"   /   /   ", 2, true});

	while (!fringe.empty())
	{
		//cout << "Top of fringe: " << fringe.top() << endl;
		if (fringe.top().hasNextNode())
		{
			fringe.top().expandNextNode(fringe);
		}
		else
		{
			if (fringe.size() > 1)
			{
				fringe.top().updateParent();
			}
			else
			{
				// We're at the root node, so check the best move now
				auto m = Move{1,1};
				EXPECT_EQ(m, fringe.top().getBestMove());
			}
			fringe.pop();
		}
	}
}
