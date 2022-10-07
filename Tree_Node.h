#include <iostream>
using namespace std;

#ifndef TREE_NODE
#define TREE_NODE

template <class T>
class Node {

private:
    T* data;
    Node* left;
    Node* right;
    Node* parent;
    int height;

public:
    Node(){
        data = NULL;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
    }

    Node(T* pdata) {
        data = pdata;
        left = NULL;
        right = NULL;
        parent = NULL;
        height = 1;
    }

    T* Get_Data(){
        return data;
    }
    void Set_Data(T* new_data){
        data = new_data;
    }

    Node* Get_Left(){
        return left;
    }
    void Set_Left(Node* new_left){
        left = new_left;
    }

    Node* Get_Right(){
        return right;
    }
    void Set_Right(Node* new_right){
        right = new_right;
    }

    Node* Get_Parent(){
        return parent;
    }
    void Set_Parent(Node* new_parent){
        parent = new_parent;
    }

    int Get_height(){
        return height;
    }
    void Set_Height(int new_height){
        height = new_height;
    }

};

#endif
