#include "AVL_Tree.h"
#include "Room.h"
#include "List.h"
#include "Point.h"
#include "Map.h"

using namespace std;

int main() {
    /*auto prueba_habitacion = new Room(1);
    prueba_habitacion->generate_tunnel();
    prueba_habitacion->get_tunnel()->get_tunnel()->smart_print_tree();


    auto lista= new List<Point>();
    lista->add(new Point(0,0));
    if(lista->find_data_coords(new Point(0,0))!=-1){
        cout<<"found it"<<endl;
    }*/
    auto mapa=new Map();
    mapa->generate_map();
    cout<<mapa->get_num_rooms()<<endl;
    cout<<mapa->get_main_room()->get_tunnel()<<endl;

}