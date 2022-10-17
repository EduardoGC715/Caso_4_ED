#include "AVL_Tree.h"
#include "Room.h"
using namespace std;

int main() {
    auto prueba_habitacion = new Room(1);
    prueba_habitacion->generate_tunnel();
    prueba_habitacion->get_tunnel()->get_tunnel()->smart_print_tree();

}