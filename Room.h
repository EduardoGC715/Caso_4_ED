#include "Tunnel.h"
#include <iostream>
#include <cstdlib>
#ifndef ROOM
#define ROOM

class Room {
private:
    Tunnel *tunnel;
    Room* doors[4];
    int room_id;
public:
    Room(){
        tunnel = nullptr;
        doors[0]=nullptr;//North
        doors[1]=nullptr;//South
        doors[2]=nullptr;//East
        doors[3]=nullptr;//West
        room_id=0;
    }
    Room(int proom_id){
        tunnel = nullptr;
        doors[0]=nullptr;//North
        doors[1]=nullptr;//South
        doors[2]=nullptr;//East
        doors[3]=nullptr;//West
        room_id=proom_id;
    }
    void Generate_tunnel(){
        int tunnel_prob = rand() % 100;
        if (tunnel_prob<66){
            tunnel = new Tunnel();
        }
    }
};

#endif
