#include "Tree_Node.h"
#include <iostream>

#ifndef AVL_TREE
#define AVL_TREE

template <class T>
class AVL_Tree{
private:
    Tree_Node<T>* m_root;

public:
    AVL_Tree(){
        m_root = nullptr;
    }

    int max(int t_x, int t_y) {
        return (t_x > t_y) ? t_x : t_y;
    }
    int height(Tree_Node<T>* t_node) {
        if (t_node == nullptr)
            return 0;
        return t_node->get_height();
    }
    int get_balance_factor(Tree_Node<T>* t_node) {
        if (t_node == nullptr)
            return 0;
        return height(t_node->get_left()) - height(t_node->get_right());
    }
    /*Tree_Node<T> *node_with_min_value(Tree_Node<T>* t_node) {
        Tree_Node<T>* current = t_node;
        while (current->get_left() != NULL)
            current = current->get_left();
        return current;
    }*/
    //hard to explain... needs drawing to fully understand...
    Tree_Node<T>* right_rotate(Tree_Node<T>* t_node) {
        t_node->get_left()->set_parent(t_node->get_parent());
        t_node->set_parent(t_node->get_left());
        t_node->set_left(t_node->get_parent()->get_right());
        if(t_node->get_left() != nullptr){
            t_node->get_left()->set_parent(t_node);
        }
        t_node->get_parent()->set_right(t_node);
        t_node->set_height( max(height(t_node->get_left()), height(t_node->get_right())) + 1);
        t_node->get_parent()->set_height( max(height(t_node->get_parent()->get_left()),height(t_node->get_parent()->get_right())) + 1);
        return t_node->get_parent();
    }
    //hard to explain... needs drawing to fully understand...
    Tree_Node<T>* left_rotate(Tree_Node<T> *t_node) {
        t_node->get_right()->set_parent(t_node->get_parent());
        t_node->set_parent(t_node->get_right());
        t_node->set_right(t_node->get_parent()->get_left());
        if(t_node->get_right() != nullptr){
            t_node->get_right()->set_parent(t_node);
        }
        t_node->get_parent()->set_left(t_node);
        t_node->set_height( max(height(t_node->get_right()), height(t_node->get_left())) + 1);
        t_node->get_parent()->set_height( max(height(t_node->get_parent()->get_right()),height(t_node->get_parent()->get_left())) + 1);
        return t_node->get_parent();
    }

    Tree_Node<T>* balance_tree(Tree_Node<T>* t_node){
        int balance_factor = get_balance_factor(t_node);
        if (balance_factor > 1) {
            if (get_balance_factor(t_node->get_left()) >= 0) {
                return right_rotate(t_node);
            } else {
                t_node->set_left(left_rotate(t_node->get_left()));
                return right_rotate(t_node);
            }
        }
        if (balance_factor < -1) {
            if (get_balance_factor(t_node->get_right()) <= 0) {
                return left_rotate(t_node);
            } else {
                t_node->set_right(right_rotate(t_node->get_right())) ;
                return left_rotate(t_node);
            }
        }
        return t_node;
    }

    void smart_insert_node(T* t_data,int t_key){
        m_root=insert_node(m_root,t_data,t_key);
    }
    Tree_Node<T> *insert_node(Tree_Node<T>* t_node, T* t_data, int t_key) {
        if (t_node == nullptr){
            return new Tree_Node<T>(t_data, t_key);
        }
        if (t_key <= t_node->get_key()){
            t_node->set_left(insert_node(t_node->get_left(),t_data, t_key));
            t_node->get_left()->set_parent(t_node);
        }
        else if (t_key > t_node->get_key()){
            t_node->set_right(insert_node(t_node->get_right(),t_data, t_key));
            t_node->get_right()->set_parent(t_node);
        }
        t_node->set_height(1 + max(height(t_node->get_left()), height(t_node->get_right())));
        return balance_tree(t_node);
    }

    void smart_print_tree(){
        print_tree(m_root, "", true);
    }
    void print_tree(Tree_Node<T>* t_node, std::string t_indent, bool t_last) {
        if (t_node != nullptr) {
            std::cout << t_indent;
            if (t_last) {
                std::cout << "R----";
                t_indent += "   ";
            } else {
                std::cout << "L----";
                t_indent += "|  ";
            }
            std::cout <<"height: "<<t_node->get_height()<<" key: "<< t_node->get_key() <<" data-> "<<"min:"<<t_node->get_data()->get_minerals()<<" dist:"<<t_node->get_data()->get_distance()<<" pot:"<<t_node->get_data()->get_potential()<<" ID:"<<t_node->get_data()->get_ID()<< std::endl;
            print_tree(t_node->get_left(), t_indent, false);
            print_tree(t_node->get_right(), t_indent, true);
        }
    }
    Tree_Node<T>* get_root(){
        return m_root;
    }
};
#endif