#include "Map/Map.h"

using namespace std;

int main() {
    auto mapa=new Map();
    mapa->generate_map();
    mapa->print_map();
}