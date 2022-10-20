# pragma once
# include <thread>
# include <chrono>
# include <future>
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
        int currentTurn;
        int timeLeft;

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

        void setup() {
            future<int> choice;
            string message;
            for (int index = 0; index < CREW_SIZE; ++index) {
                message = "Choose class for Miner #" + to_string(index+1);
                choice = async(optionMenu, ref(message), str_miners(), int(miners->size()));

                chrono::seconds span(timeLeft-1);
                if (choice.wait_for(span) == future_status::timeout) {
                    printf("Timed Out!\n");
                    return;
                }

                Character* selectedChar = miners->at(choice.get())->clone();
                thread_objs[index].setPlayerID(currentTurn+1);
                thread_objs[index].setCharacter(selectedChar);

                // message = "Select a strategy";
                // choice = optionMenu(message, pGame->str_strats(), pGame->strategies->size());
            }
            resumeAll();
        }

        void operator() () {
            printf("Game Start!\n");
            // init gameMap;
            initSubthreads();
            thread* setupThread = nullptr;
            for (currentTurn = 0; currentTurn < MAX_PLAYERS; ++currentTurn) {
                printf("\nPlayer #%d's Turn\n", currentTurn+1);
                timeLeft = TURN_DURATION;

                setupThread = new thread(&GameThread::setup, this);
                setupThread->detach();
                
                chrono::seconds delay(1);
                while (timeLeft >= 0) {
                    this_thread::sleep_for(delay);
                    --timeLeft;
                }

                pauseAll();
                printf("\n");
                delete setupThread;
                this_thread::sleep_for(chrono::seconds(1));
            }
            stopAll();
            
        }
};