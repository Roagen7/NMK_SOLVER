#pragma once

#include <cstdio>

class HashTable;

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

    friend bool operator==(const Board& b1, const Board& b2);

    void setFieldState(int y, int x, Field field);
    void clearFieldState(int y, int x);
    Field& getFieldState(int y, int x);

    void genPossibleMoves(Board *&moves, int& count, Field active);

    Field isFinalState(); // EMPTY == NO!
    bool isFull();

    void printState();

    int getN() const;
    int getM() const;

    void addHashTable(HashTable* hashTable);
    void removeHashTable();
    HashTable* getHashTable();

    ~Board();


private:


    Field* state;
    HashTable* htable = nullptr;


    int N; //height
    int M; //width
    int K; //winning condition

    bool checkInDirection(int y0, int x0, int dy, int dx, Field field); //check fields in the direction of {dy,dx}

};


