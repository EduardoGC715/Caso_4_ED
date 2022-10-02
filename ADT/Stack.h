# pragma once

template<typename T>
class Stack {
    public:
        virtual T* top() = 0;
        virtual void push(T* pData) = 0;
        virtual T* pop() = 0;
};