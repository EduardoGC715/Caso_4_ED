#include <iostream>

#ifndef PRIO_Q_NODE
#define PRIO_Q_NODE 1

template <class T>
class Prio_Q_Node {
private:
    T m_data;
    int m_priority;
    Prio_Q_Node *m_next;
    Prio_Q_Node *m_previous;

public:
    Prio_Q_Node(T pData, int pPriority) {
        m_data = pData;
        m_priority=pPriority;
        m_next = NULL;
        m_previous = NULL;
    }

    T getData() {
        return m_data;
    }

    int getPriority() {
        return m_priority;
    }

    Prio_Q_Node* getNext() {
        return m_next;
    }

    Prio_Q_Node* getPrevious() {
        return m_previous;
    }

    void setNext(Prio_Q_Node *pValue) {
        m_next = pValue;
    }

    void setPrevious(Prio_Q_Node *pValue) {
        m_previous = pValue;
    }
};

#endif

