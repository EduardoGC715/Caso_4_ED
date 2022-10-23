#include "Prio_Q_Node.h"
#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE 1

template <class T>
class Priority_Queue {
private:
    Prio_Q_Node<T> *first;
    Prio_Q_Node<T> *last;
    int quantity;
    Prio_Q_Node<T> *searchPosition = nullptr;
public:
    Priority_Queue() {
        first = nullptr;
        last = nullptr;
        quantity = 0;
    }

    void enqueue(T pData, int pPriority=0) {
        //Prioridad: El numero mÃ¡s pequeÃ±o va primero
        auto *newNode = new Prio_Q_Node<T>(pData, pPriority);
        if (this->quantity>0) {
            if(pPriority<this->first->getPriority()) {
                this->first->setNext(newNode);
                newNode->setPrevious(this->first);
                this->first=newNode;
            }
            else if(pPriority>=this->last->getPriority()){
                newNode->setNext(last);
                this->last->setPrevious(newNode);
                this->last = newNode;
            }
            else{
                searchPosition=this->first->getPrevious();

                while (searchPosition != NULL){
                    if (searchPosition->getPriority()>pPriority) {
                        newNode->setNext(searchPosition->getNext());
                        newNode->setPrevious(searchPosition);
                        searchPosition->getNext()->setPrevious(newNode);
                        searchPosition->setNext(newNode);
                        break;
                    }
                    else{
                        searchPosition= searchPosition->getPrevious();
                    }
                }
            }
        }
        else {
            this->first = newNode;
            this->last = newNode;
        }
        this->quantity++;
    }
    T dequeue() {
        if(!this->isEmpty()){
            T data = this->first->getData();
            if(this->first!=this->last){
                this->first=this->first->getPrevious();
                this->first->getNext()->setNext(NULL);
            }
            else{
                this->first=NULL;
                this->last=NULL;
            }
            this->quantity--;
            return data;
        }
    }

    bool isEmpty() {
        return !quantity;
    }
    int get_first_priority(){
        return first->getPriority();
    }
};
#endif
