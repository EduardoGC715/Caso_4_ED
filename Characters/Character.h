# pragma once
# include <string>
# include "../Strategy/Strategy.h"

using namespace std;

struct Character {
    protected:
        const int maxLoad;
        Strategy* strategy;
        State state;

    public:
        string name;
        int speed;
        int load;

        Character(const int pMaxLoad, int pSpeed)
        : maxLoad(pMaxLoad), speed(pSpeed), load(0)
        {}

        void setStrategy(Strategy* pStrat) {
            strategy = pStrat;
        }

        virtual Character* clone() = 0;

        virtual void executeStrategy() {
            switch (state) {
                case SEARCH:
                    strategy->searchTunnel(); break;

                case UNDERGROUND:
                    strategy->searchChamber(); break;

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