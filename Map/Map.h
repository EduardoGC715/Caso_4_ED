#include "Room.h"
#include "../DS/Point.h"
#include "../DS/List.h"
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
    Map(int t_rooms){
        m_num_rooms=t_rooms;
        m_main_room= new Room(1,new Point(0,0));
    }
    //utilidad pasar a carpeta...
    int random(int min, int max){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> minerals_distr(min,max);// set range
        return minerals_distr(gen); //generate random number
    }

    void generate_map(){
        int found;
        int pos_act = 0;
        int doors;
        int id=2;
        bool generated=false;

        Room* current_room;
        auto* current_point = new Point(0,0);

        m_used_coords.add(new Point(0,0));
        m_created_rooms.add(m_main_room);
        while(!generated){
            doors = random(2,4);
            for(int gen_doors=0;gen_doors<doors;gen_doors++){

                current_room = m_created_rooms.find_node(pos_act);
                current_point->set_point(current_room->get_coords());

                switch (random(0,3)) {
                    case 0://north
                        current_point->set_y(current_point->get_y() + 1);
                        found=m_used_coords.find_data_coords(current_point);
                        //si no encuentra el punto, esta libre...
                        if (found==-1) {
                            if(id>m_num_rooms){
                                //condicion de terminado, si la cantidad del id supera el numero de habitaciones no se pueden generar mas...
                                generated=true;
                                break;
                            }
                            //se asigna la habitacion
                            current_room->set_north(new Room(id, new Point(current_point->get_x(), current_point->get_y())));
                            current_room->get_north()->generate_tunnel();
                            current_room->get_north()->set_south(current_room);

                            //se agrega a las listas el nuevo punto utilizado y la habitación
                            m_created_rooms.add(current_room->get_north());
                            m_used_coords.add(current_room->get_north()->get_coords());
                            // se genero con exito
                            id++;

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
                        if (found==-1) {
                            if(id>m_num_rooms){
                                generated=true;
                                break;
                            }
                            current_room->set_south(new Room(id, new Point(current_point->get_x(), current_point->get_y())));
                            current_room->get_south()->generate_tunnel();
                            current_room->get_south()->set_north(current_room);

                            m_created_rooms.add(current_room->get_south());
                            m_used_coords.add(current_room->get_south()->get_coords());
                            id++;
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
                        if (found==-1) {
                            if(id>m_num_rooms){
                                generated=true;
                                break;
                            }
                            current_room->set_east(new Room(id, new Point(current_point->get_x(), current_point->get_y())));
                            current_room->get_east()->generate_tunnel();
                            current_room->get_east()->set_west(current_room);

                            m_created_rooms.add(current_room->get_east());
                            m_used_coords.add(current_room->get_east()->get_coords());
                            id++;
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
                        if (found==-1) {
                            if(id>m_num_rooms){
                                generated=true;
                                break;
                            }
                            current_room->set_west(new Room(id, new Point(current_point->get_x(), current_point->get_y())));
                            current_room->get_west()->generate_tunnel();
                            current_room->get_west()->set_east(current_room);

                            m_created_rooms.add(current_room->get_west());
                            m_used_coords.add(current_room->get_west()->get_coords());
                            id++;
                        }
                        else{
                            Room* aux= m_created_rooms.find_node(found);
                            current_room->set_west(aux);
                            aux->set_east(current_room);
                        }
                        break;
                }
            }
            pos_act++;
        }
    }


    void print_map(){
        for (int i=0; i<m_created_rooms.get_size();i++){
            Room* current = m_created_rooms.find_node(i);
            std::cout<<"\nHabitacion: "<<current->get_ID()<<std::endl;
            std::cout<<"Coordenadas: "<<current->get_coords()->get_x()<<" , "<<current->get_coords()->get_y()<<std::endl;

            if (current->get_north()!= nullptr){
                std::cout<<"Conectada al norte con: "<<current->get_north()->get_ID()<<std::endl;
            }
            if(current->get_south()!= nullptr){
                std::cout<<"Conectada al sur con: "<<current->get_south()->get_ID()<<std::endl;
            }
            if(current->get_east()!= nullptr){
                std::cout<<"Conectada al este con: "<<current->get_east()->get_ID()<<std::endl;
            }
            if(current->get_west()!= nullptr){
                std::cout<<"Conectada al oeste con: "<<current->get_west()->get_ID()<<std::endl;
            }

            if(current->get_tunnel()!=nullptr){
                std::cout<<"Tiene tunel: "<<current->get_tunnel()->get_tunnel_ID()<<std::endl;
                std::cout<<"Mapa del tunel: "<<std::endl;
                current->get_tunnel()->get_tunnel()->smart_print_tree();
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
