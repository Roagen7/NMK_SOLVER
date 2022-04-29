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

Board::Board(const Board &other): N(other.N), M(other.M), K(other.K), htable(other.htable) {

    state = new Field[N*M];

    for(int i = 0; i < N * M; i++){

        state[i] = other.state[i];

    }

}

Board &Board::operator=(const Board &other) {

    N = other.N;
    M = other.M;
    K = other.K;

    htable = other.htable;

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

    if(isFinalState() != EMPTY){

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

Board::Field Board::isFinalState() {
    for(int y = 0; y < N; y++){

        for(int x = 0; x < M; x++){

            auto fState = getFieldState(y,x);

            if(fState == Field::P1 || fState == Field::P2){

                bool isWin;
                isWin = checkInDirection(y, x, 1, 0, fState, K );
                isWin = isWin || checkInDirection(y, x, 0, 1, fState, K );
                isWin = isWin || checkInDirection(y, x, 1, 1, fState, K );
                isWin = isWin || checkInDirection(y, x, 1, -1, fState, K);

                if(isWin){

                    return fState;

                }
            }

        }

    }

    return EMPTY;
}

bool Board::checkInDirection(int y0, int x0, int dy, int dx, Field field, int k, bool omitFirst, bool checkMiddle) {

    int yCurrent = y0;
    int xCurrent = x0;

    int counter = 0;

    if(omitFirst){

        yCurrent += dy;
        xCurrent += dx;

    }

    while(yCurrent >= 0 && xCurrent >= 0 &&
          yCurrent < N && xCurrent < M &&
          getFieldState(yCurrent,xCurrent) == field){

        yCurrent += dy;
        xCurrent += dx;
        counter++;

    }

    if(dangerChecks(checkMiddle,yCurrent,xCurrent,dy,dx,field,counter,k)) return true;

    return counter == K;

}

int Board::getN() const {
    return N;
}

int Board::getM() const {
    return M;
}

bool Board::isFull() {

    for(int i = 0; i < N * M; i++){

        if(state[i] == Field::EMPTY){

            return false;

        }

    }

    return true;

}

void Board::addHashTable(HashTable *hashTable) {

    this->htable = hashTable;

}

void Board::removeHashTable() {

    this->htable = nullptr;

}

HashTable *Board::getHashTable() {

    return htable;

}

bool operator==(const Board &b1, const Board &b2) {

    if(b1.getM() != b2.getM() || b1.getN() != b2.getN()) return false;

    for(int i = 0; i < b1.getM() * b1.getN(); i++){

        if(b1.state[i] != b2.state[i]) return false;

    }

    return true;

}

bool Board::isDangerousState(Field toCheck, bool winning_move) {

    for(int y = 0; y < N; y++){

        for(int x = 0; x < M; x++){

            auto fState = getFieldState(y,x);

            if(fState == toCheck){

                int states = 0;
                for(int i = -1; i <= 1; i++){

                    for(int j = -1; j <= 1; j++){

                        if(!(i == 0 && j == 0)){

                            if(checkInDirection(y, x, i, j, fState, K - 1)) states++;
                            if(winning_move && checkInDirection(y, x, i, j, fState, K - 1, false,true)) return true;


                        }

                    }

                }

                if(states >= 2 || (states == 1 && winning_move)) return true;

            } else if(fState == EMPTY){

                for(int i = -1; i <= 1; i++){

                    for(int j = -1; j <= 1; j++){

                        if(!(i == 0 && j == 0)){

                            if(checkInDirection(y, x, i, j, toCheck, K - 1, true)) return true;

                        }

                    }

                }

            }



        }

    }

    return false;
}

int Board::getK() const {
    return K;
}

bool Board::dangerChecks(bool checkMiddle, int yCurrent, int xCurrent, int dy, int dx, Field field, int counter, int k) {

    bool inside = yCurrent >= 0 && xCurrent >= 0 &&
                  yCurrent < N && xCurrent < M ;

    bool dangerCheck = inside && getFieldState(yCurrent, xCurrent) == Field::EMPTY ;

    if(checkMiddle){

        bool nextInside = yCurrent + dy >= 0 && xCurrent + dx >= 0 &&
                          yCurrent + dy< N && xCurrent + dx < M ;

        bool middleCheck = nextInside && getFieldState(yCurrent+ dy,xCurrent + dx) == field;

        if(inside && dangerCheck && middleCheck){

            return counter == K-2;


        }

    }

    if(dangerCheck && k == K-1){

        return counter == k;

    }

    return false;
}











