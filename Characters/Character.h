# pragma once
# include <string>
# include "../Interfaces/iStrategy.h"

using namespace std;

struct Character {
    protected:
        const int maxLoad;
        iStrategy* strategy;

    public:
        string name;
        int speed;
        int load;

        Character(const int pMaxLoad, int pSpeed)
        : maxLoad(pMaxLoad), speed(pSpeed), load(0)
        {}

        void setStrategy(iStrategy* pStrat, Map* pMap) {
            strategy = pStrat;
            strategy->init(pMap);
        }

        virtual Character* clone() = 0;

        void setMap(Map* pMap) {
            strategy->init(pMap);
            
        }

        virtual void executeStrategy() {
            switch (strategy->getState()) {
                case SEARCH:
                    strategy->searchTunnel();
                    break;

                case UNDERGROUND:
                    strategy->searchChamber();
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