#include "Tunnel.h"
#include "../ADT/Point.h"

#ifndef ROOM
#define ROOM
//change to or adapt to list Node
class Room {
private:
    Tunnel* m_tunnel;
    Room* m_doors[4];
    int m_room_ID;
    Point* m_coords;
public:
    Room(int t_room_ID,Point* t_coords){
        m_tunnel = nullptr;
        m_doors[0]=nullptr;//North
        m_doors[1]=nullptr;//South
        m_doors[2]=nullptr;//East
        m_doors[3]=nullptr;//West
        m_room_ID=t_room_ID;
        m_coords=t_coords;
    }
    void generate_tunnel(){
        int tunnel_prob = random(0,99);
        if (tunnel_prob<66){
            m_tunnel = new Tunnel(m_room_ID);
            m_tunnel->generate_chambers();

            m_tunnel->get_tunnel()->get_data()->set_distance(0);
            m_tunnel->get_tunnel()->get_data()->set_minerals(0);
            m_tunnel->get_tunnel()->get_data()->update_potential();
        }
    }

    Tunnel* get_tunnel(){
        return m_tunnel;
    }

    int get_ID(){
        return m_room_ID;
    }

    Point* get_coords(){
        return m_coords;
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
        m_doors[1]=t_south;
    }

    Room* get_east(){
        return m_doors[2];
    }
    void set_east(Room* t_east){
        m_doors[2]=t_east;
    }

    Room* get_west(){
        return m_doors[3];
    }
    void set_west(Room* t_west){
        m_doors[3]=t_west;
    }
};

#endif
