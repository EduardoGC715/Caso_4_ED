#include <iostream>

#ifndef NODE
#define NODE 1

template <class T>
class List_Node {
private:
    T *m_data;
    List_Node *m_next;
    List_Node *m_previous;

public:
    List_Node(T *t_data) {
        m_data = t_data;
        m_next = NULL;
        m_previous = NULL;
    }

    T* get_data() {
        return m_data;
    }

    List_Node* get_next() {
        return m_next;
    }

    List_Node* get_previous() {
        return m_previous;
    }

    void set_next(List_Node *t_value) {
        m_next = t_value;
    }

    void set_previous(List_Node *t_value) {
        m_previous = t_value;
    }
};

#endif

