#include <iostream>

#ifndef TREE_NODE
#define TREE_NODE

template <class T>
class Tree_Node {

private:
    T* m_data;
    int m_key;
    Tree_Node* m_left;
    Tree_Node* m_right;
    Tree_Node* m_parent;
    int m_height;

public:
    Tree_Node(T* t_data, int t_key) {
        m_data = t_data;
        m_key=t_key;
        m_left = NULL;
        m_right = NULL;
        m_parent = NULL;
        m_height = 1;
    }

    ~Tree_Node() {
        delete m_data;
        delete m_left;
        delete m_right;
    }

    T* get_data(){
        return m_data;
    }
    void set_data(T* t_data){
        m_data = t_data;
    }

    int get_key(){
        return m_key;
    }
    void set_key(int t_key){
        m_key = t_key;
    }

    Tree_Node* get_child(int pDirection) {
        if (pDirection) {
            return m_right;
        } else {
            return m_left;
        }
    }

    Tree_Node* get_left(){
        return m_left;
    }
    void set_left(Tree_Node* t_left){
        m_left = t_left;
    }

    Tree_Node* get_right(){
        return m_right;
    }
    void set_right(Tree_Node* t_right){
        m_right = t_right;
    }

    Tree_Node* get_parent(){
        return m_parent;
    }
    void set_parent(Tree_Node* t_parent){
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
