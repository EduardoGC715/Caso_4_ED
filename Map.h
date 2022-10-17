#include "Room.h"
#include <iostream>

#ifndef MAP
#define MAP

class Map {
private:
    int m_num_rooms;
    Room* m_main_room;
public:
    Map(){
        m_num_rooms=6;
        m_main_room= new Room(1);
    }

    int random(){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> minerals_distr(0,3);// set range
        return minerals_distr(gen); //generate random number
    }

    void generate_map(){
        Room* current = m_main_room;
        for(int i=2; i<=m_num_rooms;i++){
            switch (random()) {
                case 0:
                    current->set_north(new Room(i));
                    current->get_north()->set_south(current);
                    break;
                case 1:
                    current->set_south(new Room(i));
                    current->get_south()->set_north(current);
                    break;
                case 2:
                    current->set_east(new Room(i));
                    current->get_east()->set_west(current);
                    break;
                case 3:
                    current->set_west(new Room(i));
                    current->get_west()->set_east(current);
                    break;
            }
        }
    }
};

#endif
