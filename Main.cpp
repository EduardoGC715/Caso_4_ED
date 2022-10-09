#include "AVL_Tree.h"
#include "Tunnel.h"
using namespace std;

int main() {
    auto prueba_tunel = new Tunnel(1);

    prueba_tunel->generate_chambers();
    cout<<"num chambers:"<<prueba_tunel->get_num_chambers()<<endl;
    cout<<"Tunnel id:"<<prueba_tunel->get_tunnel_ID()<<endl;
    prueba_tunel->get_tunnel()->smart_print_tree();
}