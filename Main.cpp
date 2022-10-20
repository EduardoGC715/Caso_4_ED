#include "Map/Map.h"

using namespace std;
//utilizar constantes e implementarlas
int main() {
    auto mapa=new Map(15);
    mapa->generate_map();
    mapa->print_map();
}