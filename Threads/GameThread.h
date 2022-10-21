# pragma once
# include <thread>
# include <chrono>
# include <future>
# include <unordered_map>
# include "CharacterThread.h"
# include "../ADT/List.h"
# include "../ADT/Queue.h"
# include "../utils/ioUtils.h"
# include "../Map/Map.h"

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

        Map* gameMap;
        CharacterThread* thread_objs;
        thread* sub_threads;

        minerHash* miners;
        stratHash* strategies;

        GameThread(int pPlayers, int pDuration, int pCrewSize, minerHash* pMiners, stratHash* pStrats)
        : MAX_PLAYERS(pPlayers), TURN_DURATION(pDuration), CREW_SIZE(pCrewSize) {
            // gameMap = nullptr;
            thread_objs = new CharacterThread[CREW_SIZE];
            sub_threads = new thread[CREW_SIZE];
            miners = pMiners;
            strategies = pStrats;
        }

        ~GameThread() {
            // delete gameMap;
            delete[] thread_objs;
            delete[] sub_threads;
        }

        void setMap(Map* pMap) {
            gameMap = pMap;
        }

        string* str_miners() {
            string* options = new string[miners->size()];
            for (int key = 1; key <= miners->size(); ++key) {
                options[key - 1] = miners->at(key)->name;
            }
            return options;
        }

        string* str_strats() {
            string* options = new string[strategies->size()];
            for (int key = 1; key <= strategies->size(); ++key) {
                options[key - 1] = strategies->at(key)->name;
            }
            return options;
        }

        void resumeAll() {
            for (int index = 0; index < CREW_SIZE;) {
                thread_objs[index++].resume();
                this_thread::sleep_for(chrono::seconds(1));
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
            Character* selectedChar;
            iStrategy* selectedStrat;
            chrono::seconds span;
            for (int index = 0; index < CREW_SIZE; ++index) {
                // Miner input
                message = "Choose class for Miner #" + to_string(index+1);
                choice = async(optionMenu, ref(message), str_miners(), int(miners->size()));
                span = chrono::seconds(timeLeft);
                if (choice.wait_for(span) == future_status::timeout) {
                    printf("Timed Out!\n");
                    return;
                }
                selectedChar = miners->at(choice.get())->clone();

                
                // Strategy input
                message = "Select a strategy";
                choice = async(optionMenu, ref(message), str_strats(), int(strategies->size()));
                span = chrono::seconds(timeLeft);
                if (choice.wait_for(span) == future_status::timeout) {
                    printf("Timed Out!\n");
                    return;
                }
                selectedStrat = strategies->at(choice.get())->clone();

                // Finish setup #index
                selectedChar->setStrategy(selectedStrat, gameMap);
                thread_objs[index].setPlayerID(currentTurn+1);
                thread_objs[index].setCharacter(selectedChar);
            }
            resumeAll();
        }

        void operator() () {
            printf("Game Start!\n");
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