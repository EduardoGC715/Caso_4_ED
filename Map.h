#include "Room.h"
#include <iostream>

#ifndef MAP
#define MAP

class Map {
private:
    int m_num_rooms;
public:
    Map(){
        m_num_rooms=6;
    }
    void generate_map(){
        for(int i=1; i<=m_num_rooms;i++){

        }
    }
};

#endif
