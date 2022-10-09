#include "Chamber.h"
#include "AVL_Tree.h"
#include <iostream>
#include <random>

#ifndef TUNNEL
#define TUNNEL

class Tunnel {
private:
    AVL_Tree<Chamber>* m_tunnel;
    int m_max_distance;
    int m_num_chambers;
    int m_tunnel_ID;

public:
    Tunnel(int t_tunnel_ID){
        m_tunnel = new AVL_Tree<Chamber>();
        m_max_distance=720;
        m_num_chambers=0;
        m_tunnel_ID=t_tunnel_ID;
    }

    void generate_chambers(){
        int distance_counter=m_max_distance;
        int distance;
        int minerals;
        int chamber_ID;
        while(distance_counter>0){
            m_num_chambers++;

            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> minerals_distr(1,20);// set range

            minerals=minerals_distr(gen); //generate random number
            std::cout<<"\nminerals "<<minerals<<std::endl;

            std::uniform_int_distribution<> distance_distr(10,80);

            distance=distance_distr(gen);
            std::cout<<"distance "<<distance<<std::endl;

            std::cout<<"potential "<<distance*minerals<<std::endl;

            chamber_ID=m_tunnel_ID*10+m_num_chambers;
            m_tunnel->smart_insert_node(new Chamber(minerals,distance,chamber_ID),minerals*distance);
            distance_counter=distance_counter-distance;
        }
    }

    int get_num_chambers(){
        return m_num_chambers;
    }
    int get_tunnel_ID(){
        return m_tunnel_ID;
    }
    AVL_Tree<Chamber>* get_tunnel(){
        return m_tunnel;
    }

};

#endif
