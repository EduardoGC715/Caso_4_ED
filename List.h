#include "List_Node.h"
#include "Point.h"
#ifndef LIST
#define LIST 1

template <class T>
class List {
private:
    List_Node<T> *m_first;
    List_Node<T> *m_last;
    int m_quantity;

public:
    List() {
        m_first = nullptr;
        m_last = nullptr;
        m_quantity = 0;
    }

    void add(T *t_data) {
        auto *new_node = new List_Node<T>(t_data,m_quantity);
        if (m_quantity > 0) {
            new_node->set_previous(m_last);
            m_last->set_next(new_node);
        } else {
            m_first = new_node;
        }
        m_last = new_node;
        m_quantity++;
    }

    T* find_node(int t_key) {
        T* result = nullptr;
        List_Node<T>* current = m_first;

        if (t_key < get_size()){
            while(t_key > 0) {
                current = current->get_next();
                t_key--;
            }
            result = current->get_data();
        }
        return result;
    }

    bool find_data(T t_data){
        for(int i=0; i<m_quantity; i++){
            if (t_data == &find_node(i)){
                return true;
            }
        }
        return false;
    }

    List_Node<T>* get_first() {
        m_first;
    }

    int get_size() {
        return m_quantity;
    }

    bool is_empty() {
        return !m_quantity;
    }
};

#endif

