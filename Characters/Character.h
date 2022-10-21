# pragma once
# include <string>
# include "CharacterState.h"
# include "../Interfaces/iStrategy.h"

using namespace std;

struct Character {
    protected:
        const int maxLoad;
        iStrategy* strategy;
        State state;

        List<Room>* currentRoom;
        List<RandOption>* roomOptions;

        List<Path>* currentPath;
        List<RandOption>* pathOptions;

    public:
        string name;
        int speed;
        int load;

        Character(const int pMaxLoad, int pSpeed)
        : maxLoad(pMaxLoad), state(SEARCH), speed(pSpeed), load(0)
        {
            currentRoom = new List<Room>;
            roomOptions = new List<RandOption>;
            currentPath = new List<Path>;
            pathOptions = new List<RandOption>;
        }

        void setStrategy(iStrategy* pStrat) {
            strategy = pStrat;
        }

        virtual Character* clone() = 0;

        void setMap(Map* pMap) {
            currentRoom->push(pMap->get_main_room());
            roomOptions->push(new RandOption(4));
        }

        virtual void executeStrategy() {
            switch (state) {
                case SEARCH:
                    strategy->searchTunnel(currentRoom, roomOptions, currentPath);
                    break;

                case UNDERGROUND:
                    strategy->searchChamber(currentPath, pathOptions);
                    break;

                case MINING:
                    strategy->mineChamber(); break;

                case RETRIEVE:
                    strategy->retrieveMineral(); break;

                case UNAVAILABLE:
                default:
                    break;
            }
        }
};