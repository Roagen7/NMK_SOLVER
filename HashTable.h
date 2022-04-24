#pragma once

#include <cstdlib>

#define HTABLE_SIZE 100003

class HashTable {

public:

    HashTable();

    void set(unsigned long hash, int val);
    int get(unsigned long hash) const;

    bool isSet(unsigned long hash) const;
    bool isEmpty() const;
    int getSize() const;

private:

    bool* dataIsSet;
    int* dataVals;
    int size = HTABLE_SIZE;

    bool empty = true;

};

