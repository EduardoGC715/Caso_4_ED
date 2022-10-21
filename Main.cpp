# include <thread>
# include "Characters/Explorer.h"
# include "Characters/Freighter.h"
# include "Characters/Mole.h"
# include "Threads/GameThread.h"
# include "Map/Map.h"

# define PLAYERS 2
# define DURATION 20
# define MINERS 1
# define ROOMS 15
using namespace std;

//utilizar constantes e implementarlas
int main() {
    auto mapa=new Map(ROOMS);
    mapa->generate_map();
    mapa->print_map_info();
    mapa->print_relations_map();
    mapa->print_graphic_map();

    minerHash* miners = new minerHash;
    miners->emplace(1, new Explorer);
    miners->emplace(2, new Freighter);
    miners->emplace(3, new Mole);

    stratHash* strats = new stratHash;

    GameThread game(PLAYERS, DURATION, MINERS, miners, strats);
    game.setMap(mapa);
    thread gameThread(ref(game));
    gameThread.join();

    delete miners;
    delete strats;
    return 0;
}