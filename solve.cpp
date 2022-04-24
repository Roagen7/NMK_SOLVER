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

    delete[] moves;
    return optimalVal;

}

unsigned long solve::hash(Board *board) {

    unsigned long hash = 0;

    for(int y = 0; y < board->getN(); y++){

        for(int x = 0; x < board->getM(); x++){

            if(board->getFieldState(y,x) != Board::Field::EMPTY){

                hash ^= randTable(board,y,x);

            }
        }
    }

    return hash % (int) pow(3,board->getN() * board->getM());

}

long solve::randTable(Board* board,int y, int x, bool first, bool last){

    static long* table = new long[board->getN() * board->getM() * 2];

    if(first){

        for(int i = 0; i < board->getM() * board->getN() * 2; i++){

            table[i] = rand();

        }

    }

    if(last){

        delete[] table;

        return -1;

    }


    return table[x + y * board->getM() + ((long)board->getFieldState(y,x)-1)*2];

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