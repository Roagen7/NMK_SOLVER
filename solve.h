// learning resources for the implementation
// algorithm
// https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
// optimization
// lecture - alpha-beta prunning
// https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-5-zobrist-hashing/?ref=lbp - hash function for hashtable

//info
//P1 - maximizer P2 - minimizer

#pragma once

#include <climits>
#include <cmath>

#include "Board.h"
#include "HashTable.h"

#define EVAL_MIN -10000 //P2 WINS
#define EVAL_MAX 10000 //P1 WINS
#define EVAL_TIE 0


namespace solve {


    unsigned long hash(Board* board, int size);
    long randTable(Board* board,int y, int x, bool first = false, bool last = false);

    Board bestMove(Board* board, Board::Field activePlayer);
    int eval(Board* board); // board evaluation
    int minimax(Board* board, Board::Field activePlayer, int alpha, int beta ,int depth = 0); // move evaluation

    int maximizer(Board* board, Board* moves, int numOfMoves, int alpha, int beta, int depth); // optimal val for maximizer
    int minimizer(Board* board, Board* moves, int numOfMoves, int alpha, int beta, int depth); // optimal val for minimizer

    bool cutState(Board* board, Board::Field activePlayer,int depth,int& optimalVal);



    Board::Field solve(Board* board, int activePlayer); // solve the game
    Board::Field simulate(Board* board, int activePlayer); // play the game (debug)

}