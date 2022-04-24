#include "HashTable.h"


HashTable::HashTable() {

    dataVals = new List[size];
    dataIsSet = new bool[size];


    for(int i = 0; i < size; i++){

        dataIsSet[i] = false;

    }

}

void HashTable::set(unsigned long hash, int val, Board* board) {

    empty = false;
    dataIsSet[hash] = true;
    dataVals[hash].Push({*board,val});

}

int HashTable::get(unsigned long hash, Board* board) const {

    List& dvs = dataVals[hash];

    for(int i = 0; i < dvs.len(); i++){

        if(dvs[i].board == *board) return dvs[i].minmax;

    }

    return 0;

}

bool HashTable::isSet(unsigned long hash, Board* board) const {

    if(!dataIsSet[hash]) return false;

    List& dvs = dataVals[hash];

    for(int i = 0; i < dvs.len(); i++){

        if(dvs[i].board == *board) return true;

    }

    return false;

}

int HashTable::getSize() const {
    return size;
}

bool HashTable::isEmpty() const {
    return empty;
}

HashTable::~HashTable() {

    delete[] dataVals;
    delete[] dataIsSet;

}
