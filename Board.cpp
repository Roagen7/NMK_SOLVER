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

    if(isFinalState()){

        return;

    }


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

bool Board::isFinalState() {
    for(int y = 0; y < N; y++){

        for(int x = 0; x < M; x++){

            auto fState = getFieldState(y,x);

            if(fState == Field::P1 || fState == Field::P2){

                bool isWin;
                isWin = checkInDirection(y,x,1,0,fState);
                isWin = isWin || checkInDirection(y,x,0,1,fState);
                isWin = isWin || checkInDirection(y,x,1,1,fState);
                isWin = isWin || checkInDirection(y,x,1,-1,fState);

                if(isWin){

                    return true;

                }
            }

        }

    }

    return false;
}

bool Board::checkInDirection(int y0, int x0, int dy, int dx, Field field) {

    int yCurrent = y0;
    int xCurrent = x0;

    int counter = 0;

    while(yCurrent >= 0 && xCurrent >= 0 &&
          yCurrent < N && xCurrent < M &&
          getFieldState(yCurrent,xCurrent) == field){

        yCurrent += dy;
        xCurrent += dx;
        counter++;

    }

    return counter == K;

}









