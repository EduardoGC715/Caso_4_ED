# pragma once
# include <string>
# include "../Interfaces/iStrategy.h"

using namespace std;

struct Character {
    protected:
        const int maxLoad;
        iStrategy* strategy;

        void display_action() {
            string indentation = "";
            for (int index = 0; index < ID; ++index) {
                indentation.append("    ");
            }
            printf("\n%s#%d) %s: %s\n", indentation.c_str(), ID, name.c_str(), strategy->message.c_str());
        }

    public:
        bool* isDone;
        int ID;
        string name;
        int speed;
        int load;

        Character(const int pMaxLoad, int pSpeed)
        : maxLoad(pMaxLoad), speed(pSpeed), load(0)
        {}

        ~Character() {
            delete strategy;
        }

        virtual Character* clone() = 0;

        void setStrategy(iStrategy* pStrat, Map* pMap, PlayerScore* pScore) {
            strategy = pStrat;
            strategy->init(&speed, &load, &maxLoad, pMap, pScore);
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
                    strategy->mineChamber();
                    break;

                case RETRIEVE:
                    strategy->retrieveMineral();
                    break;
                
                case SCORE:
                    strategy->score_minerals();
                    break;

                case UNAVAILABLE:
                case DONE:
                    *isDone = true;
                    return;
            }
            display_action();
        }
};