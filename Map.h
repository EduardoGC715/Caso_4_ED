#include "Room.h"
#include "Point.h"
#include "List.h"
#include <iostream>
#include <map>

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
        List<Point> used_coords;
        List<Room> created_rooms;

        Room* current_room = m_main_room;
        Point* current_point = new Point(0,0);

        used_coords.add(current_point);
        created_rooms.add(current_room);

        for(int i=2; i<=m_num_rooms;i++){
            switch (random()) {
                case 0://north
                    current_point

                    current_room->set_north(new Room(i));
                    current_room->get_north()->set_south(current_room);
                    break;
                case 1://south
                    current_room->set_south(new Room(i));
                    current_room->get_south()->set_north(current_room);
                    break;
                case 2://east
                    current_room->set_east(new Room(i));
                    current_room->get_east()->set_west(current_room);
                    break;
                case 3://west
                    current_room->set_west(new Room(i));
                    current_room->get_west()->set_east(current_room);
                    break;
            }
        }
    }
};

#endif
