/**********************************************
Name: Dustin Sherer
Coding 06
Purpose: Assignment designed to better understand the 
    linked-list data structure through building one.
**********************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

#include "data.h"

class LinkedList {

public:

    LinkedList();
    ~LinkedList();

    bool addNode(int, std::string*);
    bool deleteNode(int);
    bool getNode(int, Data*);
    void printList(bool = false);
    int getCount();
    bool clearList();
    bool exists(int);

private:

    bool addNewHead(Node*&, Node*&, bool&);
    bool addNewTail(Node*&, Node*&, bool&);
    bool insertNodeAtCurrent(Node*&, Node*&, bool&);
    void allocateNode(Node*&, int, std::string*);
    bool deleteHeadNode(Node*&, Node*&, bool&);
    bool deleteTailNode(Node*&, bool&);
    bool deleteNodeAtCurrent(Node*&, bool&);
    void findTail(Node*&);

    // "This class ain't big enough for two of us" - Node* head
    Node* head;

};

#endif // LINKEDLIST_H