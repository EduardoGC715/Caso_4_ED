#include "Room.h"
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

    int find_key(int t_value,std::unordered_map<int,int> t_map){
        for(int i = 0; i <= t_map.size(); i++){
            if (t_map[i]==t_value){
                return i;
            }
        }
        return -1;
    }

    void generate_map(){
        int num_doors;
        int found;
        int rand_dir;
        int dir_room;

        std::unordered_map<int,int> directions;
        directions[0]=1;
        directions[1]=-1;
        directions[2]=2;
        directions[3]=-2;

        Room* current_room;
        Point* current_point=new Point(0,0);

        m_rooms[1]=m_main_room;

        for(int num_rooms = 2, aux_iter = 1;num_rooms<=m_num_rooms;aux_iter++){
            num_doors = random(2,4);
            for(int doors=0;doors<num_doors;doors++){

                current_room = m_rooms[aux_iter];
                current_point->set_point(current_room->get_coords());

                rand_dir=random(0,3);
                dir_room=directions[rand_dir];
                int key=find_key(dir_room*-1,directions);
                if(rand_dir<2){
                    current_point->set_y(current_point->get_y() + dir_room);
                }
                else {
                    current_point->set_x(current_point->get_x() + dir_room/2);
                }

                found=find_room_coords(current_point);
                if (found==-1 && num_rooms<=m_num_rooms){

                    auto new_room= new Room(num_rooms, new Point(current_point->get_x(), current_point->get_y()));
                    current_room->set_direction(rand_dir, new_room);
                    new_room->set_direction(key,current_room);
                    //current_room->get_direction(rand_dir)->generate_tunnel();
                    m_rooms[num_rooms]=new_room;
                    num_rooms++;
                }
                else if(found!=-1){
                    current_room->set_direction(rand_dir,m_rooms[found]);
                    m_rooms[found]->set_direction(find_key(dir_room*-1,directions),current_room);
                }
            }
        }
    }

    void print_map_info(){
        for (int i=1;i<=m_rooms.size();i++)
        {
            Room*current = m_rooms[i];
            std::cout<<"\nHabitacion: "<<current->get_ID()<<std::endl;
            std::cout<<"Coordenadas: "<<current->get_coords()->get_x()<<" , "<<current->get_coords()->get_y()<<std::endl;

            if (current->get_direction(0)!= nullptr){
                std::cout<<"Conectada al norte con: "<<current->get_direction(0)->get_ID()<<std::endl;
            }
            if(current->get_direction(1)!= nullptr){
                std::cout<<"Conectada al sur con: "<<current->get_direction(1)->get_ID()<<std::endl;
            }
            if(current->get_direction(2)!= nullptr){
                std::cout<<"Conectada al este con: "<<current->get_direction(2)->get_ID()<<std::endl;
            }
            if(current->get_direction(3)!= nullptr){
                std::cout<<"Conectada al oeste con: "<<current->get_direction(3)->get_ID()<<std::endl;
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
            if (current->get_direction(0)!= nullptr){
                std::cout<<" [N:"<<current->get_direction(0)->get_ID();
            }
            else{
                std::cout<<" [N:0";
            }
            if (current->get_direction(1)!= nullptr){
                std::cout<<" ,S:"<<current->get_direction(1)->get_ID();
            }
            else{
                std::cout<<" ,S:0";
            }
            if (current->get_direction(2)!= nullptr){
                std::cout<<" ,E:"<<current->get_direction(2)->get_ID();
            }
            else{
                std::cout<<" ,E:0";
            }
            if (current->get_direction(3)!= nullptr){
                std::cout<<" ,W:"<<current->get_direction(3)->get_ID();
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
