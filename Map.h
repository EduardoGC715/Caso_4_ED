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
    List<Point> m_used_coords;
    List<Room> m_created_rooms;
public:
    Map(){
        m_num_rooms=6;
        m_main_room= new Room(1);
    }

    int random(int min, int max){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> minerals_distr(min,max);// set range
        return minerals_distr(gen); //generate random number
    }

    void generate_map(){
        bool generated;
        int found;

        Room* current_room;
        auto* current_point = new Point(0,0);

        m_used_coords.add(new Point(0,0));
        m_created_rooms.add(m_main_room);

        for(int i=2; i<=m_num_rooms;i++){

            int doors = random(2,4);

            for(int j=0;j<doors;j++){

                current_room = m_created_rooms.find_node(i-2);
                generated = false;

                while(!generated){

                    switch (random(0,3)) {
                        case 0://north
                            current_point->set_y(current_point->get_y() + 1);
                            found=m_used_coords.find_data_coords(current_point);
                            //si no encuentra el punto, esta libre...
                            if (found==-1) {

                                //se asigna la habitacion
                                current_room->set_north(new Room(i));
                                current_room->get_north()->generate_tunnel();
                                current_room->get_north()->set_south(current_room);

                                //se agrega a las listas el nuevo punto utilizado y la habitación
                                m_created_rooms.add(current_room->get_north());
                                m_used_coords.add(new Point(current_point->get_x(), current_point->get_y()));

                                // se genero con exito
                                generated = true;
                            }
                            else{
                                Room* aux= m_created_rooms.find_node(found);
                                current_room->set_north(aux);
                                aux->set_south(current_room);
                            }
                            break;

                        case 1://south
                            current_point->set_y(current_point->get_y() - 1);
                            found=m_used_coords.find_data_coords(current_point);
                            if (!m_used_coords.find_data_coords(current_point)) {

                                current_room->set_south(new Room(i));
                                current_room->get_south()->generate_tunnel();
                                current_room->get_south()->set_north(current_room);

                                m_created_rooms.add(current_room->get_south());
                                m_used_coords.add(new Point(current_point->get_x(), current_point->get_y()));

                                generated = true;
                            }
                            else{
                                Room* aux= m_created_rooms.find_node(found);
                                current_room->set_south(aux);
                                aux->set_north(current_room);
                            }
                            break;

                        case 2://east
                            current_point->set_x(current_point->get_x() + 1);
                            found=m_used_coords.find_data_coords(current_point);
                            if (!m_used_coords.find_data_coords(current_point)) {

                                current_room->set_east(new Room(i));
                                current_room->get_east()->generate_tunnel();
                                current_room->get_east()->set_west(current_room);

                                m_created_rooms.add(current_room->get_east());
                                m_used_coords.add(new Point(current_point->get_x(), current_point->get_y()));

                                generated = true;
                            }
                            else{
                                Room* aux= m_created_rooms.find_node(found);
                                current_room->set_east(aux);
                                aux->set_west(current_room);
                            }
                            break;

                        case 3://west
                            current_point->set_x(current_point->get_x() - 1);
                            found=m_used_coords.find_data_coords(current_point);
                            if (!m_used_coords.find_data_coords(current_point)) {

                                current_room->set_west(new Room(i));
                                current_room->get_west()->generate_tunnel();
                                current_room->get_west()->set_east(current_room);

                                m_created_rooms.add(current_room->get_west());
                                m_used_coords.add(new Point(current_point->get_x(), current_point->get_y()));

                                generated = true;
                            }
                            else{
                                Room* aux= m_created_rooms.find_node(found);
                                current_room->set_west(aux);
                                aux->set_east(current_room);
                            }
                            break;
                    }
                }
            }
        }
    }

    int get_num_rooms(){
        return m_num_rooms;
    }

    Room* get_main_room(){
        return m_main_room;
    }

    List<Point> get_used_coords(){
        return m_used_coords;
    }
    List<Room> get_created_rooms(){
        return m_created_rooms;
    }
};

#endif
