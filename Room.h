#include "Tunnel.h"
#include <iostream>
#include <cstdlib>

//cambiar a nodo generico
#ifndef ROOM
#define ROOM
//change to or adapt to list Node
class Room {
private:
    Tunnel* m_tunnel;
    Room* m_doors[4];
    int m_room_ID;
public:
    Room(int proom_id){
        m_tunnel = nullptr;
        m_doors[0]=nullptr;//North
        m_doors[1]=nullptr;//South
        m_doors[2]=nullptr;//East
        m_doors[3]=nullptr;//West
        m_room_ID=proom_id;
    }
    void Generate_Tunnel(){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, 100);// set range
        int tunnel_prob = distr(gen); //generate de random number
        if (tunnel_prob<=66){
            m_tunnel = new Tunnel(m_room_ID);
        }
    }
    Tunnel* Get_Tunnel(){
        return m_tunnel;
    }
};

#endif
