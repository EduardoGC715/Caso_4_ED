#include "Tree_Node.h"
#include <iostream>

#ifndef AVL_TREE
#define AVL_TREE

template <class T>
class AVL_Tree{
private:
    Node<T>* m_root;

public:
    AVL_Tree(){
        m_root = nullptr;
    }

    int max(int t_x, int t_y) {
        return (t_x > t_y) ? t_x : t_y;
    }
    int height(Node<T>* t_node) {
        if (t_node == nullptr)
            return 0;
        return t_node->get_height();
    }
    int get_balance_factor(Node<T>* t_node) {
        if (t_node == nullptr)
            return 0;
        return height(t_node->get_left()) - height(t_node->get_right());
    }

    //standarize
    Node<T>* right_rotate(Node<T>* y) {
        Node<T>* x = y->get_left();
        Node<T>* T2 = x->get_right();
        x->set_right(y);
        y->set_left(T2);
        y->set_height( max(height(y->get_left()), height(y->get_right())) + 1);
        x->set_height( max(height(x->get_left()),height(x->get_right())) + 1);
        return x;
    }
    //standarize
    Node<T>* left_rotate(Node<T> *x) {
        Node<T> *y = x->get_right();
        Node<T> *T2 = y->get_left();
        y->set_left(x);
        x->set_right(T2);
        x->set_height( max(height(x->get_left()), height(x->get_right())) + 1);
        y->set_height( max(height(y->get_left()), height(y->get_right())) + 1);
        return y;
    }

    Node<T> *smart_insert_node(T* t_data,int t_key){
        m_root=insert_node(m_root,t_data,t_key);
    }
    Node<T> *insert_node(Node<T>* t_node,T* t_data,int t_key) {
        if (t_node == nullptr){
            return new Node<T>(t_data,t_key);
        }
        if (t_key < t_node->get_key()){
            t_node->set_left(insert_node(t_node->get_left(),t_data, t_key));
        }
        else if (t_key > t_node->get_key()){
            t_node->set_right(insert_node(t_node->get_right(),t_data, t_key));
        }
        else{
            return t_node;
        }

        t_node->set_height(1 + max(height(t_node->get_left()), height(t_node->get_right())));
        int balance_factor = get_balance_factor(t_node);
        if (balance_factor > 1) {
            if (t_key < t_node->get_left()->get_key()) {
                return right_rotate(t_node);
            } else if (t_key > t_node->get_left()->get_key()) {
                t_node->set_left(left_rotate(t_node->get_left()));
                return right_rotate(t_node);
            }
        }
        if (balance_factor < -1) {
            if (t_key > t_node->get_right()->get_key()) {
                return left_rotate(t_node);
            } else if (t_key < t_node->get_right()->get_key()) {
                t_node->set_right(right_rotate(t_node->get_right()));
                return left_rotate(t_node);
            }
        }
        return t_node;
    }

    void smart_print_tree(std::string indent){
        print_tree(m_root, indent, true);
    }
    void print_tree(Node<T> *root, std::string indent, bool last) {
        if (root != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "   ";
            } else {
                std::cout << "L----";
                indent += "|  ";
            }
            std::cout << root->get_key() << std::endl;
            print_tree(root->get_left(), indent, false);
            print_tree(root->get_right(), indent, true);
        }
    }
};

#endif