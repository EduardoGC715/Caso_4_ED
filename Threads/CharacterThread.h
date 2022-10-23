# pragma once
# include <chrono>
# include "../utils/ioUtils.h"
# include "../Characters/Character.h"

class CharacterThread {
    private:
        int playerID;
        int ID;
        bool isRunning;
        bool isReady;
        Character* miner;

    public:
        CharacterThread()
        {}

        CharacterThread(int pID)
        : ID(pID), isRunning(true), isReady(false), miner(nullptr)
        {}

        ~CharacterThread() {
            delete miner;
        }

        void setPlayerID(int pPlayer) {
            playerID = pPlayer;
        }

        void resume() {
            isReady = true;
        }

        void pause() {
            isReady = false;
        }

        void stop() {
            isRunning = false;
        }

        void setCharacter(Character* pMiner) {
            miner = pMiner;
        }

        void operator() () {
            while (isRunning) {
                while (! isReady) {
                    std::this_thread::yield();
                }
                
                printf("#%d) %s: ", ID, miner->name.c_str());
                miner->executeStrategy();
                // printf("(%d) CharThread #%d: %s\n", playerID,ID, miner->name.c_str());
                std::this_thread::sleep_for(chrono::seconds(1)); // Comentar para turbo debug B)
            }
        }
};