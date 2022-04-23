#pragma once

#include <climits>

#include "Board.h"

#define EVAL_MIN -1
#define EVAL_MAX 1
#define EVAL_TIE 0

//notes:
//P1: maximizer
//P2: minimizer
//P1 wins = 1
//P2 wins = -1
//TIE = 0

// learning resource for the algorithm
// https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/

namespace solve {

    Board bestMove(Board* board, Board::Field activePlayer);
    int eval(Board* board); // board evaluation
    int minimax(Board* board, Board::Field activePlayer, int depth = 0); // move evaluation

    Board::Field solve(Board* board, int activePlayer); // solve the game

}