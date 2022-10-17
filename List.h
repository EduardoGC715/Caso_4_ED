#include "List_Node.h"

#ifndef LIST
#define LIST 1

template <class T>
class List {
private:
    List_Node<T> *m_first;
    List_Node<T> *m_last;
    int m_quantity;
    List_Node<T> *searchPosition = nullptr;

public:
    List() {
        m_first = nullptr;
        m_last = nullptr;
        m_quantity = 0;
    }

    void add(T *t_data) {
        auto *new_node = new List_Node<T>(t_data);
        if (m_quantity > 0) {
            new_node->set_previous(m_last);
            m_last->set_next(new_node);
        } else {
            m_first = new_node;
        }
        m_last = new_node;
        m_quantity++;
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

    T* find_node(int t_position) {
        T* result = nullptr;
        searchPosition = m_first;

        if (t_position < get_size()) {
            while(t_position > 0) {
                searchPosition = searchPosition->get_next();
                t_position--;
            }
            result = searchPosition->get_data();
        }

        return result;
    }

    void insert_node(int t_position, T *t_data) {

        if (t_position < get_size() && m_first != nullptr) {
            auto *new_node = new List_Node<T>(t_data);
            //Llamado de find para actualizar puntero searchPosition.(No borrar)
            T* result = find_node(t_position);

            new_node->set_next(searchPosition);
            if (searchPosition->get_previous() != nullptr) {
                //Anterior a newNodo es el (anterior de searchPosition)
                new_node->set_previous(searchPosition->get_previous());
                //El siguiente al (anterior de searchPosition) es newNodo
                searchPosition->get_previous()->set_next(new_node);
                //El anterior de searchPosition es NewNodo
                searchPosition->set_previous(new_node);

            } else {
                m_first = new_node;
            }

            m_quantity++;
        } else {
            add(t_data);
        }
    }

    bool delete_node(int t_position) {
        bool result = false;
        if (m_first!=nullptr && t_position < get_size()) {
            List_Node<T> *search = m_first;
            if (t_position != 0) {
                //Llamado de find para actualizar puntero searchPosition. (No borrar)

                T* data = find_node(t_position);
                //desenlaza *anterior de searchPosition
                searchPosition->get_previous()->set_next(searchPosition->get_next());

                if (searchPosition == m_last) {
                    //Actualiza puntero last.
                    m_last = searchPosition->get_previous();
                    m_last->set_next(NULL);
                }
                else{
                    //Desenlaza *siguiente de searchPosition. Solo si no es el ultimo.
                    searchPosition->get_next()->set_previous(searchPosition->get_previous());
                }
                searchPosition->set_next(NULL);
                searchPosition->set_previous(NULL);

            } else {
                m_first = m_first->get_next();
                search->set_next(NULL);
                delete search;
            }
            m_quantity--;
        }
        return result;
    }
};

#endif

