#include <iostream>

#ifndef NODE

#define NODE 1

using namespace std;

// 1. pasar este nodo a doblemente enlazado
template <class T>
class List_Node {
private:
    T *data;
    List_Node *next;
    List_Node *previous;

public:
    List_Node() {
        data = NULL;
        next = NULL;
        previous = NULL;
    }

    List_Node(T *pData) {
        this->data = pData;
        next = NULL;
        previous = NULL;
    }

    T* getData() {
        return data;
    }

    List_Node* getNext() {
        return next;
    }

    List_Node* getPrevious() {
        return previous;
    }

    void setNext(List_Node *pValue) {
        this->next = pValue;
    }

    void setPrevious(List_Node *pValue) {
        this->previous = pValue;
    }
};

#endif

