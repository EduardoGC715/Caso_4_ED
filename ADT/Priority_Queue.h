#include "Node.h"
#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE 1

template <class T>
class Queue {
private:
    Node<T> *first;
    Node<T> *last;
    int quantity;
    Node<T> *searchPosition = nullptr;
public:
    Queue() {
        first = nullptr;
        last = nullptr;
        quantity = 0;
    }

    void enqueue(T pData, int pPriority=0) {
        //Prioridad: El numero mÃ¡s pequeÃ±o va primero
        Node<T> *newNode = new Node<T>(pData, pPriority);
        if (this->quantity>0) {
            if(pPriority<this->first->getPriority()) {
                cout<<"agrego "<<newNode->getData()<<" al principio"<<endl;
                this->first->setNext(newNode);
                newNode->setPrevious(this->first);
                this->first=newNode;
            }
            else if(pPriority>=this->last->getPriority()){
                cout<<"agrego "<<newNode->getData()<<" al final"<<endl;
                newNode->setNext(last);
                this->last->setPrevious(newNode);
                this->last = newNode;
            }
            else{
                cout<<"busco el lugar del "<<newNode->getData()<<endl;
                searchPosition=this->first->getPrevious();

                while (searchPosition != NULL){
                    cout<<"comparo "<<searchPosition->getPriority()<<" "<<newNode->getPriority()<<endl;
                    if (searchPosition->getPriority()>pPriority) {
                        cout<<"agrego "<<newNode->getData()<<" antes del "<<searchPosition->getData()<<endl;
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
            cout<<"agrego "<<newNode->getData()<<" al principio ya que esta vacia"<<endl;
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
};
#endif
