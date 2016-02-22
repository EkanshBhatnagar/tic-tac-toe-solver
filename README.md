# tic-tac-toe-solver v1.0.0

Tic Tac Toe Solver is a command-line implementation of Tic Tac Toe where the human player faces an AI that can't lose. 

##Notes on compiling and running##

1. It uses C++14 features, so compile using -std=c++14 with gcc/g++.
2. The tests directory contains unit tests for the Googletest framework. You can ignore it if you just want to run the program. If you want to run the tests, link in gtest_main.a and pthread, and make sure the compiler can find the gtest headers in one of your include directories.

##About the algorithm##

The program uses minimax with alpha-beta pruning and a heuristic based on the distance and number of ways to reach a win or lose state.

###Minimax with alpha-beta pruning###

Minimax with alpha-beta pruning is a standard AI algorithm for finding the best move in two-player, zero sum games such as Tic Tac Toe. It explores the game tree in a depth-first manner to find limits on the best outcome that can be reached from each part of the game tree, given that the opponent will be playing smart as well.

The current implementation of the algorithm has two features:

1. As a DFS-based tree-search algorithm, minimax can be expressed simply as a recursive algorithm. However, for efficiency Tic Tac Toe Solver implements it in an iterative fashion, using std::stack and adding extra variables to the Node class to replace what would be local variables in a recursive implementation.
2. The depth of the search is limited to 1. This arguably makes minimax with alpha-beta pruning redundant, but experimentation showed that allowing a deeper search caused the AI to dismiss good moves simply because it assumed the human player would play perfectly and force a tie anyway. Perhaps this is a consequence of the chosen heuristic, which implements its own primitive form of lookahead to immediately determine the best move. Generally in AI, the stronger your heuristic, the less you have to look ahead, so this isn't completely unexpected.

As it stands, the current implemention serves as a starting point for further experimentation, or for an AI in a more complicated game such as four or five in a row, with larger game boards. 

###Heuristics###

The heuristic considers a possible move from a game state and records the changes to the number of ways to win or lose in however many moves.

In documentation, game states are expressed as something like "XOX/OXO/ X ", where the first 3 are the first row, and so on.

As an example of the heuristic, take the initial blank game board. Common sense says that the best move is to take the center square, and that is what the heuristic suggests as well. To see why, consider that when you take the center square, you are 1 move closer to winning along either diagonal, the center column, or the center row, and you've blocked your opponent from scoring in any of those ways. The heuristic for that could be represented like so:

<pre>Heuristic{ WaysToWin{ 0,0,4,-4 }, WaysToLose{ 0,0,0,-4 } }</pre>

The WaysToWin array stores the number of ways to win in 0, 1, 2, or 3 moves. This means that you've lost 4 ways to win in 3 moves, but gained 4 ways to win in 2 moves, which is true when you think about it. You've also eliminated 4 ways to reach a lose state in 3 moves. The WaysToLose array is similar.

Comparing two heuristics will tell us which of two possible moves is better, given the same starting board state. One caveat is that the code will allow you to compare heuristics from moves based on unrelated board states, though you should never have a reason for doing so. What you want is to know the best move given a single current or hypothetical board state.

To find which of two moves is better, the algorithm simply compares the heuristics:

<pre>HeuristicA{ WaysToWin{ 0,0,4,-4 }, WaysToLose{ 0,0,0,-4 } } // Taking the center square</pre>

<pre>HeuristicB{ WaysToWin{ 0,0,3,-3 }, WaysToLose{ 0,0,0,-3 } } // Taking a corner</pre>

<pre>HeuristicC{ WaysToWin{ 0,0,2,-2 }, WaysToLose{ 0,0,0,-2 } } // Taking a middle edge</pre>


And there it becomes obvious that taking the center square is the optimal move.

The heuristic comparison algorithm also prioritizes moves that win in fewer moves, or that prevent a loss in fewer moves.

#Notes on this version#

Tic Tac Toe Solver v1.0.0
3:50PM February 22, 2016

The unit tests all pass, and you can play against the AI and never win.

##Todo##

- Code review
- Test with the AI going second
- Test with two AIs
- Add command-line options specifying who goes first 
- Test and debug with search depth > 1
- Verify that pruning is done correctly

##Known issues##

- Increasing the search depth to 2 causes the AI to ignore good moves, even if it still plays well.
- Increasing the search depth beyond 2 causes the AI to make bad moves. Needs bug fixing.
