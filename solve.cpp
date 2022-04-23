#include "solve.h"


Board solve::bestMove(Board *board, Board::Field activePlayer) {

    Board* moves = nullptr;
    int numOfMoves,bestMoveVal, bestMoveIx = 0;;


    board->genPossibleMoves(moves,numOfMoves,activePlayer);

    if(activePlayer == Board::Field::P1){

        bestMoveVal = INT_MIN;

        for(int i = 0; i < numOfMoves; i++){

            int val = minimax(moves + i,Board::Field::P2,INT_MIN,INT_MAX);

            if(val > bestMoveVal) {

                bestMoveVal = val;
                bestMoveIx = i;

            }

        }

    } else {

        bestMoveVal = INT_MAX;

        for(int i = 0; i < numOfMoves; i++){

            int val = minimax(moves + i, Board::Field::P1, INT_MIN, INT_MAX);

            if(val < bestMoveVal){

                bestMoveVal = val;
                bestMoveIx = i;

            }

        }

    }

    Board bestMove = moves[bestMoveIx];

    delete[] moves;

    return bestMove;

}


int solve::eval(Board *board) {

    switch(board->isFinalState()){

        case Board::Field::P1:
            return EVAL_MAX;

        case Board::Field::P2:
            return EVAL_MIN;

        case Board::Field::EMPTY:
            return EVAL_TIE;

    }

    return EVAL_TIE;

}

int solve::minimax(Board *board, Board::Field activePlayer, int alpha, int beta, int depth) {

    Board* moves = nullptr;
    int numOfMoves, optimalVal;

    Board::Field state = board->isFinalState();
    if(state != Board::Field::EMPTY || board->isFull()) return eval(board);

    board->genPossibleMoves(moves,numOfMoves,activePlayer);

    if(activePlayer == Board::Field::P1){

        optimalVal = INT_MIN;

        for(int i = 0; i < numOfMoves; i++){

            int newVal = minimax(moves + i,Board::Field::P2, alpha, beta, depth+1);
            optimalVal = optimalVal > newVal ? optimalVal : newVal; // max(optimalVal, newVal)
            alpha = alpha > optimalVal ? alpha : optimalVal;

            if(alpha >= beta) break;

        }

        delete[] moves;
        return optimalVal - depth;

    } else {

        optimalVal = INT_MAX;

        for(int i = 0; i < numOfMoves; i++){

            int newVal = minimax(moves + i, Board::Field::P1, alpha, beta ,depth+1);
            optimalVal = optimalVal < newVal ? optimalVal : newVal; // min(optimalVal,newVal)
            beta = beta < optimalVal ? beta : optimalVal;

            if(alpha >= beta) break;

        }

        delete[] moves;
        return optimalVal + depth;

    }

}

Board::Field solve::solve(Board *board, int activePlayer) {

    auto turn = (Board::Field) activePlayer;

    while(board->isFinalState() == Board::Field::EMPTY && !board->isFull()){

        Board m = bestMove(board,turn);
        *board = m;
        turn = turn == Board::Field::P1 ? Board::Field::P2 : Board::Field::P1;

    }

    return board->isFinalState();

}