#include "HashTable.h"


HashTable::HashTable() {

    dataVals = new int[size];
    dataIsSet = new bool[size];

    for(int i = 0; i < size; i++){

        dataIsSet[i] = false;

    }

}

void HashTable::set(unsigned long hash, int val) {

    empty = false;

    dataIsSet[hash] = true;
    dataVals[hash] = val;

}

int HashTable::get(unsigned long hash) const {
    return dataVals[hash];
}

bool HashTable::isSet(unsigned long hash) const {
    return dataIsSet[hash];
}

int HashTable::getSize() const {
    return size;
}

bool HashTable::isEmpty() const {
    return empty;
}
