#include "Board.h"

#include <string.h>

#define MAX_STRLEN 256

void handleInput();
void commandGenAllPosMov();

void printAllPossibleMoves(Board* board, int activePlayer);


int main() {

//    int testBoard[] = {
//            1,2,2,
//            1,1,1,
//            2,2,1
//    };
//
//    Board board(3,3,3, testBoard);
//
//    bool v = board.isFinalState();
//
//    printAllPossibleMoves(&board,2);

    handleInput();



    return 0;
}


void printAllPossibleMoves(Board* board, int activePlayer){


    Board* moves = nullptr;
    int num;
    board->genPossibleMoves(moves,num,(Board::Field)activePlayer);

    printf("%d\n",num);

    for(int i = 0; i < num; i++){

        moves[i].printState();

    }

    delete[] moves;


}

void handleInput(){

    char command[MAX_STRLEN];

    while(scanf("%s",command) == 1){

        if(strcmp(command,"GEN_ALL_POS_MOV") == 0){

            commandGenAllPosMov();

        }

    }

}

void commandGenAllPosMov(){

    int N, M, K, active;
    scanf("%d %d %d %d", &N, &M, &K, &active);

    int* state = new int[N * M];

    for(int i = 0; i < N * M; i++){

        scanf("%d", state + i);

    }

    Board board(N,M,K,state);
    delete[] state;
    printAllPossibleMoves(&board,active);


}