#include "Room.h"

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
        int rand_dir;
        int directions[4]={1,-1,2,-2};
        int dir_room;

        Room* current_room;
        Point* current_point;
        auto* aux_point = new Point(0,0);

        m_rooms[1]=m_main_room;

        while(!gen_map){
            doors = random(2,4);
            for(int gen_doors=0;gen_doors<doors;gen_doors++){
                current_room = m_rooms[aux_itr];
                current_point= current_room->get_coords();

                rand_dir=random(0,3);
                dir_room=directions[rand_dir];

                if(rand_dir<2){
                    aux_point->set_y(aux_point->get_y()+dir_room);
                }
                else {
                    aux_point->set_x(current_point->get_x() + dir_room/2);
                }
                found=find_room_coords(aux_point);
                if (found==-1){
                    if(id>m_num_rooms){
                        gen_map=true;
                        break;
                    }
                    current_room->get_doors()[dir_room]=new Room(id, new Point(aux_point->get_x(), aux_point->get_y()));
                    current_room->get_doors()[dir_room]->get_doors()[dir_room*-1]=current_room;

                    m_rooms[id]=current_room->get_doors()[dir_room];
                    id++;
                }
                else{
                    current_room->get_doors()[dir_room]=m_rooms[found];
                    m_rooms[found]->get_doors()[dir_room*-1]=current_room;
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

    struct array
    {
        int values[4];
    };

    array* get_min_max(){
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
        auto values = new array();
        values->values[0]=min_x;
        values->values[1]=max_x;
        values->values[2]=min_y;
        values->values[3]=max_y;
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
                std::cout<<" [N:0";
            }
            if (current->get_south()!= nullptr){
                std::cout<<" ,S:"<<current->get_south()->get_ID();
            }
            else{
                std::cout<<" ,S:0";
            }
            if (current->get_east()!= nullptr){
                std::cout<<" ,E:"<<current->get_east()->get_ID();
            }
            else{
                std::cout<<" ,E:0";
            }
            if (current->get_west()!= nullptr){
                std::cout<<" ,W:"<<current->get_west()->get_ID();
            }
            else{
                std::cout<<" W:0";
            }
            std::cout<<"]\n";
        }
    }

    void print_graphic_map(){
        Room*current;
        auto coords=get_min_max();
        int min_x=coords->values[0];
        int max_x=coords->values[1];
        int min_y=coords->values[2];
        int max_y=coords->values[3];

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
                    if(current->get_ID()<10){
                        std::cout<<"[00"<<current->get_ID()<<"] ";
                    }
                    else if(current->get_ID()<100){
                        std::cout<<"[0"<<current->get_ID()<<"] ";
                    }
                    else{
                        std::cout<<"["<<current->get_ID()<<"] ";
                    }
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
