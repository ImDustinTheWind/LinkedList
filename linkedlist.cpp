/**********************************************
Name: Dustin Sherer
Coding 06
Purpose: Assignment designed to better understand the
    linked-list data structure through building one.
**********************************************/

#include "linkedlist.h"

LinkedList::LinkedList() {
    head = NULL;

}

LinkedList::~LinkedList() {
    clearList();
}

//**********************************************
// takes (id/data) and adds new node into list
// while keeping in sequential (id) order
//**********************************************
bool LinkedList::addNode(int dataID, std::string* dataData) {
    Node* newNode;
    bool isSuccess = false, nodePlaced = false;
    if (dataID > 0 && *dataData != "") {//first, data check
        if ((head == NULL) || (dataID < head->data.id)) {
            allocateNode(newNode, dataID, dataData);
            isSuccess = addNewHead(head, newNode, nodePlaced);
        }
        Node* current = head;
        while (!nodePlaced && (dataID != current->data.id)) {
            if (dataID < current->data.id) { //[NEW-ID < CURRENT-ID] [INSERT NEW-NODE AT CURRENT]
                allocateNode(newNode, dataID, dataData);
                isSuccess = insertNodeAtCurrent(current, newNode, nodePlaced);
            }
            else if (current->next == NULL) { //[END-OF-LIST] [ADD NEW TAIL]
                allocateNode(newNode, dataID, dataData);
                isSuccess = addNewTail(current, newNode, nodePlaced);
            }
            else { current = current->next; }
        }
    }
    return isSuccess;
}

//**********************************************
// takes (id) and deletes corresponding node in
// list, if it exists, while keeping in 
// sequential (id) order
//**********************************************
bool LinkedList::deleteNode(int iD) {
    bool isSuccess = false;
    bool done = false;
    Node* current = this->head;
    while ((iD > 0) && current && !done) {
        if ((current->next == NULL) && (current->data.id != iD)) {
            done = true;
        }
        else if ((current->prev == NULL) && (current->data.id == iD)) {
            isSuccess = deleteHeadNode(current, current->next, done);
        }
        else if ((current->next == NULL) && (current->data.id == iD)) {
            isSuccess = deleteTailNode(current, done);
        }
        else if (current->data.id == iD) {
            isSuccess = deleteNodeAtCurrent(current, done);
        }
        else { current = current->next; }
    } 
    return isSuccess;
}

//**********************************************
// takes (id) and returns node data through 
// reference if node exists
//**********************************************
bool LinkedList::getNode(int iD, Data* refNode) {
    bool isSuccess = false;
    Node* current = this->head;
    refNode->id = -1;
    refNode->data = "";
    while (current) {
        if (current->data.id == iD) {
            refNode->id = current->data.id;
            refNode->data = current->data.data;
            isSuccess = true;
        }
        current = current->next;
    }
    return isSuccess;
}

//**********************************************
// ONLY FUNCTION ALLOWED TO PRINT - prints out
// list either forwards or backwards, depending
// on bool passed as argument
//**********************************************
void LinkedList::printList(bool backward /*= false*/) {
    Node* current = this->head;
    if (!backward) {
        while (current) {
            std::cout << current->data.id << ": " << current->data.data << std::endl;
            current = current->next;
        }
    }
    else {
        findTail(current);
        while (current) {
            std::cout << current->data.id << ": " << current->data.data << std::endl;
            current = current->prev;
        }
    }
}

//**********************************************
// returns number of nodes in list
//**********************************************
int LinkedList::getCount() {
    Node* current = this->head;
    int count = 0;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

//**********************************************
// deletes all allocated memory to list and 
// points "head" back to NULL
//**********************************************
bool LinkedList::clearList() {
    Node* current = this->head;
    bool isSuccess = false;
    if (head) {
        findTail(current);              //go to end of list
        while (current->prev != NULL) {//if current is NOT head node
            deleteTailNode(current, isSuccess);
        }
        delete current; //when only head remains - delete
        this->head = NULL; //point head back to NULL to reset
        isSuccess = true;
    }
    return isSuccess;
}

//**********************************************
// takes (id) and returns bool value if the 
// corresponding node is found in list
//**********************************************
bool LinkedList::exists(int iD) {
    bool isSuccess = false;
    Node* current = this->head;
    while (current) {
        if (current->data.id == iD) {
            isSuccess = true;
        }
        current = current->next;
    }
    return isSuccess;
}

//**********************************************
// helper function that adds new head-node,completes 
// task in case of first node inserted in list, or 
// if new (id) is less than existing head
//**********************************************
bool LinkedList::addNewHead(Node*& head, Node*& newNode, bool& placed) {
    if ((head == NULL)) { //[HEAD IS NULL] [NEW-NODE BECOMES HEAD]
        newNode->next = NULL;
    }
    else {     //[NEW-ID < HEAD-ID] [NEW-NODE INSERTED AS HEAD]
        head->prev = newNode;
        newNode->next = head;
    }
    newNode->prev = NULL;
    head = newNode;
    placed = true;
    return  placed;
}

//**********************************************
// helper function that adds node to tail of list
//**********************************************
bool LinkedList::addNewTail(Node*& current, Node*& newNode, bool& placed) {
    newNode->next = NULL;
    newNode->prev = current;
    current->next = newNode;
    placed = true;
    return  placed;
}

//**********************************************
// helper function that adds node at current 
// spot in the linked list
//**********************************************
bool LinkedList::insertNodeAtCurrent(Node*& current, Node*& newNode, bool& placed) {
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    placed = true;
    return  placed;
}

//**********************************************
// helper function to allocate memory for new node
//**********************************************
void LinkedList::allocateNode(Node*& newNode, int dID, std::string* dData) {
        newNode = new Node;
        newNode->data.id = dID;
        newNode->data.data = *dData;
}

//**********************************************
// helper function to delete head node, whether
// head is only node or not
//**********************************************
bool LinkedList::deleteHeadNode(Node*& toDelete, Node*& nextNode, bool& done) {
    if ((toDelete->next != NULL)) { //if head is not also tail
        nextNode->prev = NULL;
    }
    this->head = nextNode;
    delete toDelete;
    done = true;
    return done;
}

//**********************************************
// helper function to delete tail node
//**********************************************
bool LinkedList::deleteTailNode(Node*& current, bool& done) {
    Node* toDelete = current; //toDelete points to last node
    current = current->prev; //current points to last node's prev
    current->next = NULL;   //current points to NULL instead of last node
    delete toDelete;       //delete last node  
    done = true;
    return done;
}

//**********************************************
// helper function to delete node at current
//**********************************************
bool LinkedList::deleteNodeAtCurrent(Node*& current, bool& done) {
    Node* pre = current->prev;
    Node* post = current->next;
    pre->next = post;
    post->prev = pre;
    delete current;
    done = true;
    return done;
}

//**********************************************
// helper function moves Node pointer to tail
//**********************************************
void LinkedList::findTail(Node*& current) {
    bool tail = false;
    while (current && !tail) {
        if (current->next) {
            current = current->next;
        }
        else {
            tail = true;
        }
    }
}
