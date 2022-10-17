#include "Tunnel.h"
#include <iostream>
#include <cstdlib>

#ifndef ROOM
#define ROOM
//change to or adapt to list Node
class Room {
private:
    Tunnel* m_tunnel;
    Room* m_doors[4];
    int m_room_ID;
public:
    Room(int t_room_ID){
        m_tunnel = nullptr;
        m_doors[0]=nullptr;//North
        m_doors[1]=nullptr;//South
        m_doors[2]=nullptr;//East
        m_doors[3]=nullptr;//West
        m_room_ID=t_room_ID*1000;
    }
    void generate_tunnel(){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(1, 100);// set range
        int tunnel_prob = distr(gen); //generate de random number
        if (tunnel_prob<=66){
            m_tunnel = new Tunnel(m_room_ID+1);
            m_tunnel->generate_chambers();

            m_tunnel->get_tunnel()->get_root()->get_data()->set_distance(0);
            m_tunnel->get_tunnel()->get_root()->get_data()->set_minerals(0);
            m_tunnel->get_tunnel()->get_root()->get_data()->update_potential();
        }
    }

    Tunnel* get_tunnel(){
        return m_tunnel;
    }

    Room* get_north(){
        return m_doors[0];
    }
    void set_north(Room* t_north){
        m_doors[0]=t_north;
    }

    Room* get_south(){
        return m_doors[1];
    }
    void set_south(Room* t_south){
        m_doors[0]=t_south;
    }

    Room* get_east(){
        return m_doors[2];
    }
    void set_east(Room* t_east){
        m_doors[0]=t_east;
    }

    Room* get_west(){
        return m_doors[3];
    }
    void set_west(Room* t_west){
        m_doors[0]=t_west;
    }
};

#endif
