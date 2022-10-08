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
        m_root = NULL;
    }

    int max(int t_x, int t_y) {
        return (t_x > t_y) ? t_x : t_y;
    }
    int height(Node<T>* t_node) {
        if (t_node == NULL)
            return 0;
        return t_node->Get_Height();
    }
    int get_balance_factor(Node<T>* t_node) {
        if (t_node == NULL)
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

    Node *insertNode(Node<T>* t_node,T* t_data,int t_key) {
        // Find the correct postion and insert the node
        if (t_node == NULL)
            return new Node<T>(t_data,t_key);
        if (t_key < t_node->get_key()){
            t_node->set_left(insertNode(t_node->left, t_key));
        }
        else if (t_key > t_node->get_key())
            t_node->set_right(insertNode(t_node->right, t_key));
        else
            return t_node;

        // Update the balance factor of each node and
        // balance the tree
        node->height = 1 + max(height(node->left),
                               height(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (key < node->left->key) {
                return rightRotate(node);
            } else if (key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (key > node->right->key) {
                return leftRotate(node);
            } else if (key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }
};

#endif
