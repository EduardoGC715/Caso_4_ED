# include <thread>
# include "Characters/Explorer.h"
# include "Characters/Freighter.h"
# include "Characters/Mole.h"
# include "Threads/GameThread.h"

# define PLAYERS 2
# define DURATION 10
# define MINERS 3

int main() {
    minerHash* miners = new minerHash;
    miners->emplace(1, new Explorer);
    miners->emplace(2, new Freighter);
    miners->emplace(3, new Mole);

    stratHash* strats = new stratHash;

    GameThread game(PLAYERS, DURATION, MINERS, miners, strats);
    thread gameThread(ref(game));
    gameThread.join();
    
    delete miners;
    delete strats;
    return 0;
}