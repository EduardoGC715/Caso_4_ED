#include "../Map/Room.h"
#include <unordered_map>

#ifndef MAP
#define MAP

class Map {
private:
    int m_num_rooms;
    Room* m_main_room;
    std::unordered_map<int,Room*> m_rooms;

public:
    Map(int t_rooms){
        m_num_rooms=t_rooms;
        //...room constructor?
        m_main_room= new Room(1,new Point(0,0));
    }

    int find_room_coords(Point* t_point){
        for(int i = 1; i <= m_rooms.size(); i++){
            if (m_rooms[i]->get_coords()->compare_point(t_point)){
                return i;
            }
        }
        return -1;
    }

    void generate_map(){
        int doors;
        int id = 2;
        int aux_itr = 1;
        int found;
        bool gen_map = false;

        Room* current_room;
        //...point constructor ?
        auto* current_point = new Point(0,0);
        auto* aux_point = new Point(0,0);

        m_rooms[1]=m_main_room;

        while(!gen_map){
            doors = random(2,4);
            for(int gen_doors=0;gen_doors<doors;gen_doors++){
                current_room = m_rooms[aux_itr];
                current_point= current_room->get_coords();
                aux_point->set_point(current_point);
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
                            current_room->get_north()->generate_tunnel();
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

                    case 1://south
                        aux_point->set_y(current_point->get_y() - 1);
                        found=find_room_coords(aux_point);
                        if (found==-1){
                            if(id>m_num_rooms){
                                gen_map=true;
                                break;
                            }
                            current_room->set_south(new Room(id, new Point(aux_point->get_x(), aux_point->get_y())));
                            current_room->get_south()->generate_tunnel();
                            current_room->get_south()->set_north(current_room);

                            m_rooms[id]=current_room->get_south();

                            id++;
                        }
                        else{
                            current_room->set_south(m_rooms[found]);
                            m_rooms[found]->set_north(current_room);
                        }
                        break;

                    case 2://east
                        aux_point->set_x(current_point->get_x() + 1);
                        found=find_room_coords(aux_point);
                        if (found==-1){
                             if(id>m_num_rooms){
                                 gen_map=true;
                                    break;
                             }
                            current_room->set_east(new Room(id, new Point(aux_point->get_x(), aux_point->get_y())));
                            current_room->get_east()->generate_tunnel();
                            current_room->get_east()->set_west(current_room);

                            m_rooms[id]=current_room->get_east();

                            id++;
                        }
                        else{
                            current_room->set_east(m_rooms[found]);
                            m_rooms[found]->set_west(current_room);
                        }
                        break;

                    case 3://west
                        aux_point->set_x(current_point->get_x() - 1);
                        found = find_room_coords(aux_point);
                        if (found==-1){
                            if(id>m_num_rooms){
                                gen_map=true;
                                break;
                            }
                            current_room->set_west(new Room(id, new Point(aux_point->get_x(), aux_point->get_y())));
                            current_room->get_west()->generate_tunnel();
                            current_room->get_west()->set_east(current_room);

                            m_rooms[id]=current_room->get_west();

                            id++;
                        }
                        else{
                            current_room->set_west(m_rooms[found]);
                            m_rooms[found]->set_east(current_room);
                        }
                        break;
                }
            }
            aux_itr++;
        }
    }


    void print_map_info(){

        for (int i=1;i<=m_rooms.size();i++)
        {
            Room*current = m_rooms[i];
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
                current->get_tunnel()->smart_print_tree();
            }
        }
    }

    int* get_min_max(){
        int min_x=0,max_x=0,min_y=0,max_y=0;
        int current_x=0;
        int current_y=0;
        Room*current;
        for (int i=1;i<=m_rooms.size();i++){
            current = m_rooms[i];
            current_x = current->get_coords()->get_x();
            current_y = current->get_coords()->get_y();
            if(current_x < min_x){
                min_x=current_x;
            }
            else if(current_x>max_x){
                max_x=current_x;
            }
            if(current_y < min_y){
                min_y=current_y;
            }
            else if(current_y>max_y){
                max_y=current_y;
            }

        }
        static int values[4]={min_x,max_x,min_y,max_y};
        return values;
    }

    void print_relations_map(){
        for (int i=1;i<=m_rooms.size();i++){
            Room*current = m_rooms[i];
            std::cout<<"#"<<current->get_ID();
            if (current->get_north()!= nullptr){
                std::cout<<" [N:"<<current->get_north()->get_ID();
            }
            else{
                std::cout<<" [N:null";
            }
            if (current->get_south()!= nullptr){
                std::cout<<" ,S:"<<current->get_south()->get_ID();
            }
            else{
                std::cout<<" ,S:null";
            }
            if (current->get_east()!= nullptr){
                std::cout<<" ,E:"<<current->get_east()->get_ID();
            }
            else{
                std::cout<<" ,E:null";
            }
            if (current->get_west()!= nullptr){
                std::cout<<" ,W:"<<current->get_west()->get_ID();
            }
            else{
                std::cout<<" W:null";
            }
            std::cout<<"]\n";
        }
    }

    void print_graphic_map(){
        Room*current;
        int* values=get_min_max();
        int min_x=values[0];
        int max_x=values[1];
        int min_y=values[2];
        int max_y=values[3];

        auto* point_itr = new Point(min_x,max_y);

        bool all = false;
        bool found;

        while(!all){
            if(point_itr->get_x()==max_x && point_itr->get_y()==min_y){
                all=true;
            }
            found=false;
            for (int i=1;i<=m_rooms.size();i++){
                current = m_rooms[i];
                if(current->get_coords()->compare_point(point_itr)){
                    std::cout<<"[ "<<current->get_ID()<<" ] ";
                    found=true;
                }
            }
            if(!found){
                std::cout<<"[   ] ";
            }
            if(point_itr->get_x()<max_x){
                point_itr->set_x(point_itr->get_x()+1);
            }
            else{
                std::cout<<std::endl;
                point_itr->set_x(min_x);
                point_itr->set_y(point_itr->get_y()-1);
            }
        }
    }

    int get_num_rooms(){
        return m_num_rooms;
    }

    Room* get_main_room(){
        return m_main_room;
    }

    auto get_rooms(){
        return m_rooms;
    }
};

#endif
