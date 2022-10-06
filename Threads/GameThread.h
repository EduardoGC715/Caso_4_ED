# pragma once
# include <thread>
# include <chrono>
# include <unordered_map>
# include "CharacterThread.h"
# include "../ADT/List.h"
# include "../ADT/Queue.h"
# include "../utils/ioUtils.h"

// TODO: Reemplazar los includes siguientes con solucion de Eduardo
# include "../ADT/Tree.h"
// # include "../GameEntities/Door.h"

class GameThread {
    private:
        const int MAX_PLAYERS;
        const int TURN_DURATION;    // In seconds
        const int CREW_SIZE;

        // Tree<Door>* gameMap;
        // Queue<BinaryNode<Chamber>>* deletionQueue;
        CharacterThread* thread_objs;
        std::thread* sub_threads;

        // TODO: Recordar incluir en parametros del constructor al implementarlos
        // std::unordered_map<int, Character*> *miners;
        // std::unordered_map<int, Strategy*> *strategies;

    public:
        GameThread(int pPlayers, int pDuration, int pCrewSize)
        : MAX_PLAYERS(pPlayers), TURN_DURATION(pDuration), CREW_SIZE(pCrewSize) {
            // gameMap = nullptr;
            // deletionQueue = new List<BinaryNode<Chamber>>;
            thread_objs = new CharacterThread[CREW_SIZE];
            sub_threads = new std::thread[CREW_SIZE];
            // miners = pMiners;
            // strategies = pStrategies;
        }

        ~GameThread() {
            // delete gameMap;
            // delete[] subThreads;
            // delete deletionQueue;
        }

        void playerSetup() {
            // Solicita personajes hasta cumplir CREW_SIZE
            // Por cada personaje, solicita una estrategia
            // Finalmente, thread_objs[i].setCharacter()

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

        void operator() () {
            // init gameMap;
            for (int index = 0; index < CREW_SIZE; ++index) {
                thread_objs[index] = CharacterThread();
                sub_threads[index] = std::thread(std::ref(thread_objs[index]));
            }

            for (int turn = 0; turn < MAX_PLAYERS; ++turn) {
                playerSetup();
                resumeAll();
                for (int seconds = 0; seconds < TURN_DURATION; ++seconds) {
                    // Remove deletionQueue.dequeue() from map
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                pauseAll();
            }
            stopAll();
        }
};