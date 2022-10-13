# pragma once
# include <thread>
# include <chrono>
# include <unordered_map>
# include "CharacterThread.h"
# include "../ADT/List.h"
# include "../ADT/Queue.h"
# include "../utils/ioUtils.h"

// TODO: Reemplazar los includes siguientes con solucion de Eduardo
// # include "../ADT/Tree.h"
// # include "../Demo/Door.h"

using namespace std;

typedef unordered_map<int, class Character*> minerHash;
typedef unordered_map<int, Strategy*> stratHash;

class GameThread;
void gameTimer(GameThread* pGame);
void setup(GameThread* pGame);

class GameThread {
    public:
        const int MAX_PLAYERS;
        const int TURN_DURATION;    // In seconds
        const int CREW_SIZE;

        bool isWaiting;
        bool isRunning;

        // Tree<Door>* gameMap;
        // Queue<BinaryNode<Chamber>>* deletionQueue;
        CharacterThread* thread_objs;
        thread* sub_threads;

        minerHash* miners;
        stratHash* strategies;

        GameThread(int pPlayers, int pDuration, int pCrewSize, minerHash* pMiners, stratHash* pStrats)
        : MAX_PLAYERS(pPlayers), TURN_DURATION(pDuration), CREW_SIZE(pCrewSize) {
            // gameMap = nullptr;
            // deletionQueue = new List<BinaryNode<Chamber>>;
            thread_objs = new CharacterThread[CREW_SIZE];
            sub_threads = new thread[CREW_SIZE];
            miners = pMiners;
            strategies = pStrats;
        }

        ~GameThread() {
            // delete gameMap;
            // delete[] subThreads;
            // delete deletionQueue;
        }

        string* str_miners() {
            string* options = new string[miners->size()];
            for (int key = 1; key <= miners->size(); ++key) {
                options[key - 1] = miners->at(key)->name;
            }
            return options;
        }

        void resumeAll() {
            for (int index = 0; index < CREW_SIZE;) {
                thread_objs[index++].resume();
            }
        }

        void pauseAll() {
            for (int index = 0; index < CREW_SIZE;) {
                thread_objs[index++].pause();
            }
        }

        void stopAll() {
            for (int index = 0; index < CREW_SIZE;) {
                thread_objs[index++].stop();
            }
        }

        void initSubthreads() {
            for (int index = 0; index < CREW_SIZE; ++index) {
                thread_objs[index] = CharacterThread(index+1);
                sub_threads[index] = thread( ref(thread_objs[index]) );
            }
        }

        void operator() () {
            printf("Game Start!\n");
            // init gameMap;
            initSubthreads();
            for (int turn = 0; turn < MAX_PLAYERS; ++turn) {
                printf("\nPlayer #%d's Turn\n", turn+1);
                thread* timeManager = new thread(gameTimer, this);
                thread* inputThread = new thread(setup, this);
                while (isRunning) {
                    if (isWaiting) {
                        this_thread::yield();
                    } else {
                        // Remove deletionQueue.dequeue() from map
                    }
                }
                timeManager->join(); delete timeManager;
                inputThread->join(); delete inputThread;
                pauseAll();
                printf("\n");
            }
            stopAll();
        }
};

void gameTimer(GameThread* pGame) {
    pGame->isRunning = true;
    chrono::seconds time(pGame->TURN_DURATION);
    this_thread::sleep_for(time);
    pGame->isRunning = false;
}

void setup(GameThread* pGame) {
    int choice;
    string message;
    pGame->isWaiting = true;
    for (int index = 0; index < pGame->CREW_SIZE; ++index) {
        message = "Choose class for Miner #" + to_string(index+1);
        choice = optionMenu(message, pGame->str_miners(), pGame->miners->size());

        Character* selectedChar = pGame->miners->at(choice)->clone();
        pGame->thread_objs[index].setCharacter(selectedChar);

        // message = "Select a strategy";
        // choice = optionMenu(message, pGame->str_strats(), pGame->strategies->size());
    }
    pGame->isWaiting = false;
    pGame->resumeAll();
    // Solicita personajes hasta cumplir CREW_SIZE
    // Por cada personaje, solicita una estrategia
    // Finalmente, thread_objs[i].setCharacter() y resumeAll()

    // Antes de implementar este metodo, considerar lo siguiente
    // Crear una libreria simple para menus de texto: ioUtils
    // Manejar hashes para seleccion de personajes y estrategias. Ej:

        /*  "Interfaz Texto"
            Seleccione personaje:
                1. Explorador
                2. Carguero
                3. Topo            */
    
        /* Donde input valido es un valor en keys: {1, 2, 3} */
    
    // Nota importante: Validacion de entradas cin para ints
}