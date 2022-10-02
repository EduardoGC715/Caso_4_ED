# pragma once

template<typename T>
class Queue {
    public:
        virtual T* getFront() = 0;
        virtual void enqueue(T* pData) = 0;
        virtual T* dequeue() = 0;
};