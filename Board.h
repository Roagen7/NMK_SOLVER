#pragma once

#include <cstdio>

class Board {

public:

    enum Field {

        EMPTY,
        P1,
        P2

    };

    Board();
    Board(int N, int M, int K); //empty board
    Board(int N, int M, int K, int* arr); //from array
    Board(const Board& other); //copy

    Board& operator=(const Board& other);

    void setFieldState(int y, int x, Field field);
    void clearFieldState(int y, int x);
    Field& getFieldState(int y, int x);

    void genPossibleMoves(Board *&moves, int& count, Field active);
    bool isFinalState();

    void printState();

    ~Board();
    bool checkInDirection(int y0, int x0, int dy, int dx, Field field);

private:


    Field* state;
    int N; //height
    int M; //width
    int K; //winning condition




};


