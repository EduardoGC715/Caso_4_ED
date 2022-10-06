# include <thread>
# include "Threads/GameThread.h"

# define PLAYERS 2
# define DURATION 120
# define MINERS 3

int main() {
    GameThread* game = new GameThread(PLAYERS, DURATION, MINERS);
}