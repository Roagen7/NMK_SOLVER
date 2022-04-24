#pragma once

#include "Board.h"

struct Pair {

    Board board;
    int minmax;

};


class List {

public:

    struct Node {

        Node* prev;
        Node* next;

        Pair val;


    } head{}, tail{};

    List(){

        head =  Node{nullptr, &tail, Board()};
        tail = Node{&head, nullptr, Board()};

    }

    void Push(Pair val){

        Node* newEl = new Node;
        newEl->next = &tail;
        newEl->prev = tail.prev;

        newEl->val = val;

        tail.prev->next = newEl;
        tail.prev = newEl;

    }

    Pair Pop(){

        Node* toPopEl = tail.prev;
        tail.prev = toPopEl->prev;
        toPopEl->prev->next = &tail;

        Pair valcpy = toPopEl->val;
        delete toPopEl;

        return valcpy;

    }

    void Remove(int ix){

        Node* current = head.next;

        for(int i = 0; i < ix; i++){

            current = current->next;

        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;


    }

    int len() const{

        auto* current = head.next;
        int l = 0;

        while(current != nullptr){

            current = current->next;
            l++;

        }

        return l - 1;

    }

    Pair& operator[](int ix) const{

        Node* current = head.next;

        for(int i = 0; i < ix; i++){

            current = current->next;

        }

        return current->val;

    }

    Node* getHead(){

        return &head;

    }

    ~List(){

        Node* current = head.next;
        while(current->next != nullptr){

            Node* nextAddr = current->next;
            delete current;

            current = nextAddr;

        }

    }



};


