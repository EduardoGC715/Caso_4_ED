# pragma once
# include <thread>
# include <future>
# include <unordered_map>
# include "../utils/ThreadUtils.h"
# include "CharacterThread.h"
# include "../ADT/List.h"
# include "../ADT/Queue.h"
# include "../utils/ioUtils.h"
# include "../Map/Map.h"
#include "../ADT/Priority_Queue.h"

using namespace std;

typedef unordered_map<int, class Character*> minerHash;
typedef unordered_map<int, iStrategy*> stratHash;

class GameThread {
    private:
        // Game Parameters
        const int MAX_PLAYERS;
        const int TURN_DURATION;    // In seconds
        const int CREW_SIZE;

        // Game Data
        Map* gameMap;
        minerHash* miners;
        stratHash* strategies;

        // Player Data
        PlayerScore* score_board;
        thread* sub_threads;
        CharacterThread* thread_objs;

        // Turn Data
        bool finishEarly;
        bool* isCharacterDone;
        int currentTurn;
        int timeLeft;

    public:
        GameThread(int pPlayers, int pDuration, int pCrewSize, minerHash* pMiners, stratHash* pStrats)
        : MAX_PLAYERS(pPlayers), TURN_DURATION(pDuration), CREW_SIZE(pCrewSize) {
            // gameMap = nullptr;
            score_board = new PlayerScore[MAX_PLAYERS];
            sub_threads = new thread[CREW_SIZE];
            thread_objs = new CharacterThread[CREW_SIZE];
            isCharacterDone = new bool[CREW_SIZE];
            
            miners = pMiners;
            strategies = pStrats;
        }

        ~GameThread() {
            delete[] thread_objs;
            delete[] sub_threads;
            delete[] score_board;
            delete gameMap;
            delete miners;
            delete strategies;
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
                sleep(1);
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

        void initScoreboard() {
            for (int index = 0; index < MAX_PLAYERS;) {
                score_board[index].setID(index++);
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
                selectedChar->isDone = isCharacterDone+index;
                selectedChar->ID = (index+1);
                selectedChar->setStrategy(selectedStrat, gameMap, score_board+currentTurn);
                thread_objs[index].setPlayerID(currentTurn+1);
                thread_objs[index].setCharacter(selectedChar);
            }
            resumeAll();
        }

        bool resetEarlyFlag() {
            for (int index = 0; index < CREW_SIZE; ++index) {
                isCharacterDone[index] = false;
            }
            return false;
        }

        bool areCharactersDone() {
            for (int index = 0; index < CREW_SIZE; ++index) {
                if (! isCharacterDone[index]) {
                    return false;
                }
            }
            return true;
        }
        void showResults() {
            auto scores = new Priority_Queue<int>();
            bool done = false;
            int index=0;
            while (index<MAX_PLAYERS) {
                if(!done){
                    int score = score_board[index].get();
                    scores->enqueue(score + index + 1, score);
                }
                else{
                    int curr_score = scores->get_first_priority();
                    int player = scores->dequeue() - curr_score;
                    printf("#%d: Player %d Score:%d\n", index, player, curr_score);
                }
                index++;
                if(!done && index==MAX_PLAYERS){
                    done=true;
                    index=0;
                }
            }

        }

        void print_all_map_data() {
            gameMap->print_map_info();
            gameMap->print_relations_map();
            gameMap->print_graphic_map();
        }

        void operator() () {
            // initMap();
            printf("Game Start!\n");
            initScoreboard();
            initSubthreads();
            thread* setupThread = nullptr;
            for (currentTurn = 0; currentTurn < MAX_PLAYERS; ++currentTurn) {
                print_all_map_data();
                printf("\nPlayer #%d's Turn\n", currentTurn+1);
                timeLeft = TURN_DURATION;

                setupThread = new thread(&GameThread::setup, this);
                setupThread->detach();

                finishEarly = resetEarlyFlag();
                while (timeLeft >= 0 && ! finishEarly) {
                    finishEarly = areCharactersDone();
                    sleep(1);
                    --timeLeft;
                }

                pauseAll();
                delete setupThread;
                printf("\nPlayer #%d's Turn Finished!\n\nLoading...\n", currentTurn+1);
                sleep(3);
            }
            showResults();
            stopAll();
        }
};