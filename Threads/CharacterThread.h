# pragma once
# include <chrono>
# include "../Characters/Character.h"

class CharacterThread
{
private:
    bool isRunning;
    bool isPaused;
    Character* miner;
    // Strategy* strategy;

    // Comparte punteros deletionQueue y gameMap de GameThread, pues los mineros
    // navegan en este y pueden colapsar secciones de un tunel
    // Tree<Door>* gameMap;
    // Queue<BinaryNode<Chamber>>* deletionQueue;

public:
    CharacterThread()
    : isRunning(true), isPaused(true)
    {}

    ~CharacterThread() {
        delete miner;
        // delete strategy;
    }

    void resume() {
        isPaused = false;
    }

    void pause() {
        isPaused = true;
    }

    void stop() {
        isRunning = false;
    }

    // TODO: Agregar parametro Strategy*
    void setCharacter(Character* pMiner) {
        miner = pMiner;
        //strategy = pStrategy;
    }

    void operator() () {
        while (isRunning) {
            while (isPaused) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
};