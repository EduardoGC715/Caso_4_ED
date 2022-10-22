#include "Chamber.h"
#include "../ADT/AVL_Tree.h"
#include "../utils/Random.h"

#ifndef TUNNEL
#define TUNNEL

class Tunnel :AVL_Tree<Chamber>{
private:
    int m_max_distance;
    int m_num_chambers;
    int m_tunnel_ID;

public:
    Tunnel(int t_tunnel_ID){
        m_max_distance=720;
        m_num_chambers=0;
        m_tunnel_ID=t_tunnel_ID;
        generate_chambers();
    }

    void generate_chambers(){
        int distance_counter=m_max_distance;
        int distance;
        int minerals;
        int chamber_ID;
        while(distance_counter>0){
            m_num_chambers++;

            minerals= random(1,20);
            distance=random(10,80);

            chamber_ID=m_tunnel_ID*100+m_num_chambers;
            auto* chamber= new Chamber(minerals,distance,chamber_ID);
            smart_insert_node(chamber,chamber->get_potential());
            distance_counter=distance_counter-distance;
        }
    }

    int get_num_chambers(){
        return m_num_chambers;
    }
    int get_tunnel_ID(){
        return m_tunnel_ID;
    }
    Tree_Node<Chamber>* get_tunnel(){
        return m_root;
    }

    void smart_print_tree(){
        print_tree(m_root, "", true);
    }
    void print_tree(Tree_Node<Chamber>* t_node, std::string t_indent, bool t_last) {
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
};

#endif
