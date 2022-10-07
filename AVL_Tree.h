#include "Tree_Node.h"
#include <iostream>

#ifndef AVL_TREE
#define AVL_TREE

template <class T>
class AVL_Tree{
private:
    Node<T>* root;

    //data
    int max_distance;
    int num_chambers;
    int tunnel_ID;
public:
    int Max(int a, int b) {
        return (a > b) ? a : b;
    }
    int Height(Node<T>* Node) {
        if (Node == NULL)
            return 0;
        return Node->Get_Height();
    }
    int Get_Balance_Factor(Node<T>* Node) {
        if (Node == NULL)
            return 0;
        return height(Node->Get_Left()) - height(Node->Get_Right());
    }

    Node<T>* Right_Rotate(Node<T>* y) {
        Node<T>* x = y->Get_Left();
        Node<T>* T2 = x->Get_Right();
        x->Set_Right(y);
        y->Set_Left(T2);
        y->Set_Height( max(height(y->Get_Left()), height(y->Get_Right())) + 1);
        x->Set_Height( max(height(x->Get_Left()),height(x->Get_Right())) + 1);
        return x;
    }
    Node<T>* Left_Rotate(Node<T> *x) {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;
        y->Set_Left(x);
        x->Set_Right(T2);
        x->Set_Height( max(height(x->left), height(x->right)) + 1);
        y->Set_Height( max(height(y->left), height(y->right)) + 1);
        return y;
    }
};

#endif
