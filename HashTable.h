#pragma once

#include <cstdlib>

#include "List.h"

#define HTABLE_SIZE 5003
#define HTABLE

class HashTable {

public:

    HashTable();
    ~HashTable();

    void set(unsigned long hash, int val, Board* board);
    int get(unsigned long hash, Board* board) const;

    bool isSet(unsigned long hash, Board* board) const;
    bool isEmpty() const;
    int getSize() const;

private:

    bool* dataIsSet;

    List* dataVals;


    int size = HTABLE_SIZE;

    bool empty = true;

};

