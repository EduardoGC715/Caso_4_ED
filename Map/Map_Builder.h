#include "Room.h"

#ifndef MAP_BUILDER
#define MAP_BUILDER

class Map_Builder{
private:
    Room* m_current_room;
    Point* m_current_point;
    std::unordered_map<int,Room*> m_doors;
public:
    Map_Builder(Room * t_main_room){
        m_current_room=t_main_room;
        m_current_point=new Point(0,0);
        
    }

    void build_room(Room* t_room, Point* t_point, Room* t_available, int t_direction){
        switch (random(0,3)) {
            case 0://north
                aux_point->set_y(current_point->get_y() + 1);
                found=find_room_coords(aux_point);
                if (found==-1){
                    if(id>m_num_rooms){
                        //condicion de terminado, si la cantidad del id supera el numero de habitaciones no se pueden generar mas...
                        gen_map=true;
                        break;
                    }
                    //se asigna la habitacion
                    current_room->set_north(new Room(id, new Point(aux_point->get_x(), aux_point->get_y())));
                    current_room->get_north()->set_south(current_room);

                    //se agrega a los maps
                    m_rooms[id]=current_room->get_north();

                    // se genero con exito
                    id++;
                }
                else{
                    current_room->set_north(m_rooms[found]);
                    m_rooms[found]->set_south(current_room);
                }
                break;
};

#endif
