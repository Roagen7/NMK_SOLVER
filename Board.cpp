#include "Board.h"

Board::Board() {

    state = nullptr;
    N = 0;
    M = 0;
    K = 0;

}


Board::Board(int N, int M, int K): N(N), M(M),K(K) {

    state = new Field[N*M];

    for(int i = 0; i < N * M; i++){

        state[i] = Field::EMPTY;

    }

}

Board::Board(int N, int M, int K, int* arr): N(N), M(M),K(K) {

    state = new Field[N*M];

    for(int i = 0; i < N * M; i++){

        state[i] = (Field) arr[i];

    }

}

Board::Board(const Board &other): N(other.N), M(other.M), K(other.K) {

    state = new Field[N*M];

    for(int i = 0; i < N * M; i++){

        state[i] = other.state[i];

    }

}

Board &Board::operator=(const Board &other) {

    N = other.N;
    M = other.M;
    K = other.K;

    delete[] state;
    state = new Field[N*M];

    for(int i = 0; i < N * M; i++){

        state[i] = other.state[i];

    }

    return *this;

}

Board::Field &Board::getFieldState(int y, int x) {
    return state[y * M + x];
}


void Board::setFieldState(int y, int x, Board::Field field) {

    getFieldState(y,x) = field;


}

void Board::clearFieldState(int y, int x) {

    setFieldState(y,x,Field::EMPTY);

}

void Board::printState() {

    for(int y = 0; y < N; y++){

        for(int x = 0; x < M; x++){

            int v = getFieldState(y,x);
            printf("%d ",v);

        }

        printf("\n");

    }


}

void Board::genPossibleMoves(Board *&moves, int& count, Field active) {

    delete[] moves;
    count = 0;
    moves = new Board[N*M];

    for(int y = 0; y < N; y++){

        for(int x = 0; x < M; x++){

            if(getFieldState(y,x) == Field::EMPTY){

                Board boardWithMove{*this};
                boardWithMove.setFieldState(y,x,active);

                moves[count++] = boardWithMove;

            }


        }

    }


}


Board::~Board() {


    delete[] state;

}









