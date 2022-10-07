#include <iostream>

#ifndef TREE_NODE
#define TREE_NODE

template <class T>
class Node {

private:
    T* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_parent;
    int m_height;

public:
    Node(){
        m_data = NULL;
        m_left = NULL;
        m_right = NULL;
        m_parent = NULL;
        m_height = 1;
    }

    Node(T* t_data) {
        m_data = t_data;
        m_left = NULL;
        m_right = NULL;
        m_parent = NULL;
        m_height = 1;
    }

    T* get_data(){
        return m_data;
    }
    void set_data(T* t_data){
        m_data = t_data;
    }

    Node* get_left(){
        return m_left;
    }
    void set_left(Node* t_left){
        m_left = t_left;
    }

    Node* get_right(){
        return m_right;
    }
    void set_right(Node* t_right){
        m_right = t_right;
    }

    Node* get_parent(){
        return m_parent;
    }
    void set_parent(Node* t_parent){
        m_parent = t_parent;
    }

    int get_height(){
        return m_height;
    }
    void set_height(int t_height){
        m_height = t_height;
    }
};
#endif
