#include <string.h>

#include "Board.h"
#include "solve.h"

#define MAX_STRLEN 256

void handleInput();
void commandGenAllPosMov(bool cut = false);

void printAllPossibleMoves(Board* board, int activePlayer, bool withCut = false);

int main() {

    int testBoard[] = {
            1,0,0,
            0,0,0,
            0,0,0
    };

    Board board(3,3,3, testBoard);
//
//    bool v = board.isFinalState();
//
//    printAllPossibleMoves(&board,1,true);

//    handleInput();


    auto state = solve::solve(&board,2);




    return 0;
}


void printAllPossibleMoves(Board* board, int activePlayer, bool withCut){


    Board* moves = nullptr;
    int num;
    board->genPossibleMoves(moves,num,(Board::Field)activePlayer);

    if(withCut){

        for(int i = 0; i < num; i++){

            if(moves[i].isFinalState()){
                printf("1\n");
                moves[i].printState();
                return;

            }

        }

    }


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

        } else if(strcmp(command,"GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0){

            commandGenAllPosMov(true);

        }



    }

}

void commandGenAllPosMov(bool cut){

    int N, M, K, active;
    scanf("%d %d %d %d", &N, &M, &K, &active);

    int* state = new int[N * M];

    for(int i = 0; i < N * M; i++){

        scanf("%d", state + i);

    }

    Board board(N,M,K,state);
    delete[] state;


    printAllPossibleMoves(&board,active, cut);


}

