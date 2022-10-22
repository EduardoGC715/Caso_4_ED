#include "Tunnel.h"
#include "../ADT/Point.h"
#include <unordered_map>
#ifndef ROOM
#define ROOM
//change to or adapt to list Node
class Room {
private:
    Tunnel* m_tunnel;
    std::unordered_map<int,Room*> m_doors;
    int m_room_ID;
    Point* m_coords;
public:
    Room(int t_room_ID,Point* t_coords){
        m_tunnel = nullptr;
        m_doors[1]=nullptr;//North
        m_doors[-1]=nullptr;//South
        m_doors[2]=nullptr;//East
        m_doors[-2]=nullptr;//West
        m_room_ID=t_room_ID;
        m_coords=t_coords;
        generate_tunnel();
    }
    void generate_tunnel(){
        int tunnel_prob = random(0,99);
        if (tunnel_prob<66){
            m_tunnel = new Tunnel(m_room_ID);

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
        return m_doors[1];
    }

    Room* get_south(){
        return m_doors[-1];
    }

    Room* get_east(){
        return m_doors[2];
    }

    Room* get_west(){
        return m_doors[-2];
    }
    std::unordered_map<int,Room*> get_doors(){
        return m_doors;
    }
};

#endif
