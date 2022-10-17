#include <iostream>

#ifndef NODE
#define NODE 1

template <class T>
class List_Node {
private:
    T *m_data;
    int m_key;
    List_Node *m_next;
    List_Node *m_previous;

public:
    List_Node(T *t_data, int t_key) {
        m_data = t_data;
        m_key = t_key;
        m_next = nullptr;
        m_previous = nullptr;
    }

    T* get_data() {
        return m_data;
    }
    void set_data(T* t_data){
        m_data = t_data;
    }

    int get_key() {
        return m_key;
    }
    void set_key(int t_key){
        m_key = t_key;
    }

    List_Node* get_next() {
        return m_next;
    }
    void set_next(List_Node *t_value) {
        m_next = t_value;
    }

    List_Node* get_previous() {
        return m_previous;
    }
    void set_previous(List_Node *t_value) {
        m_previous = t_value;
    }
};

#endif

