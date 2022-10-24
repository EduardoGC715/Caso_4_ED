# include <thread>
# include "Characters/Explorer.h"
# include "Characters/Freighter.h"
# include "Characters/Mole.h"
# include "Strategy/BoldStrategy.h"
# include "Strategy/CarefulStrategy.h"
# include "Strategy/GreedyStrategy.h"
# include "Strategy/SpitefulStrategy.h"
# include "Threads/GameThread.h"
# include "Map/Map.h"

# define PLAYERS 2
# define DURATION 120
# define MINERS 3
# define ROOMS 10
using namespace std;

//utilizar constantes e implementarlas
int main() {
    auto mapa=new Map(ROOMS);
    mapa->generate_map();

    minerHash* miners = new minerHash;
    miners->emplace(1, new Explorer);
    miners->emplace(2, new Freighter);
    miners->emplace(3, new Mole);

    stratHash* strats = new stratHash;
    strats->emplace(1, new BoldStrategy);
    strats->emplace(2, new CarefulStrategy);
    strats->emplace(3, new GreedyStrategy);
    strats->emplace(4, new SpitefulStrategy);

    GameThread game(PLAYERS, DURATION, MINERS, miners, strats);
    game.setMap(mapa);
    thread gameThread(ref(game));
    gameThread.join();
    return 0;
}