#include <string.h>
#include <cstdlib>
#include <time.h>


#include "Board.h"
#include "solve.h"
#include "HashTable.h"


#define MAX_STRLEN 256

FILE* file;


void handleInput();
void commandGenAllPosMov(bool cut = false);
void commandSolveGameState(HashTable* htable);

void printAllPossibleMoves(Board* board, int activePlayer, bool withCut = false);

int main() {

    file = fopen("../tests/custom.in","r");
    srand(time(nullptr));


    handleInput();
    fclose(file);

    solve::randTable(nullptr,0,0,false,true);


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

                delete[] moves;
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
    int counter = 0;
    HashTable htable;

    while(fscanf(file,"%s",command) == 1){

        if(strcmp(command,"GEN_ALL_POS_MOV") == 0){

            commandGenAllPosMov();

        } else if(strcmp(command,"GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0){

            commandGenAllPosMov(true);

        } else if(strcmp(command,"SOLVE_GAME_STATE") == 0){

            counter++;
            if(counter == 30596){


                int x = 0;


            }

            commandSolveGameState(&htable);

        }



    }

}

void commandGenAllPosMov(bool cut){

    int N, M, K, active;
    fscanf(file,"%d %d %d %d", &N, &M, &K, &active);

    int* state = new int[N * M];

    for(int i = 0; i < N * M; i++){

        fscanf(file,"%d", state + i);

    }

    Board board(N,M,K,state);
    delete[] state;


    printAllPossibleMoves(&board,active, cut);

}

void commandSolveGameState(HashTable* htable){

    int N, M, K, active;
    fscanf(file,"%d %d %d %d", &N, &M, &K, &active);

    int* state = new int[N * M];

    for(int i = 0; i < N * M; i++){

        fscanf(file,"%d", state + i);

    }

    Board board(N,M,K,state);
    delete[] state;

    board.addHashTable(htable);

    auto solution = solve::solve(&board,active);

    switch(solution){

        case Board::Field::EMPTY:
            printf("BOTH_PLAYERS_TIE\n");
            return;
        case Board::Field::P1:
            printf("FIRST_PLAYER_WINS\n");
            return;
        case Board::Field::P2:
            printf("SECOND_PLAYER_WINS\n");
            return;

    }

}

