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

    auto* htable = board->getHashTable();

#ifdef HTABLE

    if(htable != nullptr){

        unsigned long hashVal = solve::hash(board,htable->getSize());
        if(htable->isSet(hashVal,board)) return htable->get(hashVal,board);

    }

#endif

    Board* moves = nullptr;
    int numOfMoves, optimalVal;

    if(solve::cutState(board,activePlayer,depth,optimalVal)) return optimalVal;

    board->genPossibleMoves(moves,numOfMoves,activePlayer);

    optimalVal = Board::Field::P1 == activePlayer ?
            solve::maximizer(board,moves,numOfMoves,alpha,beta,depth)
            : solve::minimizer(board,moves,numOfMoves,alpha,beta,depth);

    delete[] moves;

    optimalVal = activePlayer == Board::P1 ? optimalVal - depth : optimalVal + depth;


#ifdef HTABLE

    if(htable != nullptr){

        unsigned long hashVal = solve::hash(board,htable->getSize());
        board->getHashTable()->set(hashVal,optimalVal,board);

    }

#endif

    return optimalVal;

}

unsigned long solve::hash(Board *board, int size) {

    unsigned long hash = 0;

    for(int y = 0; y < board->getN(); y++){

        for(int x = 0; x < board->getM(); x++){

            if(board->getFieldState(y,x) != Board::Field::EMPTY){

                hash ^= randTable(board,y,x);

            }
        }
    }

    return hash % size;

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

#ifdef HTABLE
    if(board->getHashTable() != nullptr && board->getHashTable()->isEmpty()){

        randTable(board,0,0,true);

    }
#endif

    auto turn = (Board::Field) activePlayer;

    int mx = minimax(board,turn,INT_MIN,INT_MAX);
    int maxDepth = board->getN() * board->getM() * board->getK();


    if(abs(EVAL_MAX - mx) <= maxDepth){

        return Board::P1;

    }

    if(abs(EVAL_MIN - mx) <= maxDepth){

        return Board::P2;

    }

    return Board::EMPTY;

}

Board::Field solve::simulate(Board *board, int activePlayer) {


    if(board->getHashTable() != nullptr && board->getHashTable()->isEmpty()){

        randTable(board,0,0,true);

    }

    auto turn = (Board::Field) activePlayer;

    while(board->isFinalState() == Board::Field::EMPTY && !board->isFull()){

        Board m = bestMove(board,turn);
        *board = m;
        turn = turn == Board::Field::P1 ? Board::Field::P2 : Board::Field::P1;

    }

    return board->isFinalState();

}


int solve::maximizer(Board* board, Board* moves, int numOfMoves, int alpha, int beta, int depth) {

    int optimalVal = INT_MIN;

    for(int i = 0; i < numOfMoves; i++){

        int newVal = minimax(moves + i,Board::Field::P2, alpha, beta, depth+1);
        optimalVal = optimalVal > newVal ? optimalVal : newVal; // max(optimalVal, newVal)

#ifndef HTABLE

        alpha = alpha > optimalVal ? alpha : optimalVal;
        if(beta <= alpha) break;

#endif

        if(abs(optimalVal - EVAL_MAX) <= board->getM() * board->getN())  break;

    }

    return optimalVal;

}

int solve::minimizer(Board *board, Board *moves, int numOfMoves, int alpha, int beta, int depth) {

    int optimalVal = INT_MAX;

    for(int i = 0; i < numOfMoves; i++){

        int newVal = minimax(moves + i, Board::Field::P1, alpha, beta ,depth+1);
        optimalVal = optimalVal < newVal ? optimalVal : newVal; // min(optimalVal,newVal)

#ifndef HTABLE

        beta = beta < optimalVal ? beta : optimalVal;
        if(beta <= alpha) break;

#endif

        if(abs(optimalVal - EVAL_MIN) <= board->getM() * board->getN()) break;

    }

    return optimalVal;

}

bool solve::cutState(Board *board,Board::Field activePlayer, int depth,int &optimalVal) {

    Board::Field state = board->isFinalState();

    if(state != Board::Field::EMPTY || board->isFull()){

        optimalVal = eval(board);
        return true;

    }

    if(board->isDangerousState(activePlayer,true)){

        optimalVal = activePlayer == Board::Field::P1 ? EVAL_MAX - depth : EVAL_MIN + depth;
        return true;

    }


    if(board->isDangerousState(activePlayer == Board::Field::P1 ? Board::Field::P2 : Board::Field::P1, false)){

        optimalVal = activePlayer == Board::Field::P1 ? EVAL_MIN + depth : EVAL_MAX - depth;
        return true;

    }

    return false;

}