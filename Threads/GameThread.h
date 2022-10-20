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
typedef unordered_map<int, iStrategy*> stratHash;

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
            delete[] thread_objs;
            delete[] sub_threads;
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
                sub_threads[index] = thread{ ref(thread_objs[index]) };
                sub_threads[index].detach();
            }
        }

        void timer() {
            isRunning = true;
            chrono::seconds time(TURN_DURATION);
            this_thread::sleep_for(time);
            isRunning = false;
        }

        void setup() {
            int choice;
            string message;
            isWaiting = true;
            for (int index = 0; index < CREW_SIZE; ++index) {
                message = "Choose class for Miner #" + to_string(index+1);
                choice = optionMenu(message, str_miners(), miners->size());

                Character* selectedChar = miners->at(choice)->clone();
                thread_objs[index].setCharacter(selectedChar);

                // message = "Select a strategy";
                // choice = optionMenu(message, pGame->str_strats(), pGame->strategies->size());
            }
            isWaiting = false;
            resumeAll();
        }

        void operator() () {
            printf("Game Start!\n");
            // init gameMap;
            initSubthreads();
            for (int turn = 0; turn < MAX_PLAYERS; ++turn) {
                printf("\nPlayer #%d's Turn\n", turn+1);
                thread timeManager{&GameThread::timer, this};
                thread inputThread{&GameThread::setup, this};
                
                while (isRunning) {
                    if (isWaiting) {
                        this_thread::yield();
                    } else {
                        // Remove deletionQueue.dequeue() from map
                    }
                }
                timeManager.detach();
                inputThread.detach();

                pauseAll();
                printf("\n");
            }
            stopAll();
        }
};