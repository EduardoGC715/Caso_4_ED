#include "AVL_Tree.h"

int main() {
    auto prueba_arbol = new AVL_Tree<int>();
    prueba_arbol->smart_insert_node(new int(33),33);
    prueba_arbol->smart_insert_node(new int(13),13);
    prueba_arbol->smart_insert_node(new int(53),53);
    prueba_arbol->smart_insert_node(new int(9),9);
    prueba_arbol->smart_insert_node(new int(21),21);
    prueba_arbol->smart_insert_node(new int(61),61);
    prueba_arbol->smart_insert_node(new int(8),8);
    prueba_arbol->smart_insert_node(new int(11),11);

    prueba_arbol->smart_print_tree("");
    prueba_arbol->smart_delete_node(13);
    prueba_arbol->smart_delete_node(11);
    std::cout << "After deleting " << std::endl;
    prueba_arbol->smart_print_tree("");
}