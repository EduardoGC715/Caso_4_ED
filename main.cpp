# include "Map/Map.h"
# include <thread>
# include "Characters/Explorer.h"
# include "Characters/Freighter.h"
# include "Characters/Mole.h"
# include "Threads/GameThread.h"

# define PLAYERS 2
# define DURATION 10
# define MINERS 3
# define ROOMS 25
using namespace std;

//utilizar constantes e implementarlas
int main() {
    auto mapa=new Map(ROOMS);
    mapa->generate_map();
    mapa->print_map_info();
    mapa->print_relations_map();
    mapa->print_graphic_map();

    auto mapa1=new Map(ROOMS);
    mapa1->generate_map();
    mapa1->print_map_info();
    mapa1->print_relations_map();
    mapa1->print_graphic_map();

/*
    minerHash* miners = new minerHash;
    miners->emplace(1, new Explorer);
    miners->emplace(2, new Freighter);
    miners->emplace(3, new Mole);

    stratHash* strats = new stratHash;

    GameThread game(PLAYERS, DURATION, MINERS, miners, strats);
    thread gameThread(ref(game));
    gameThread.join();

    delete miners;
    delete strats;*/
    return 0;
}