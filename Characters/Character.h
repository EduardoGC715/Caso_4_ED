# pragma once
# include <string>
# include "../Strategy/Strategy.h"

using namespace std;

struct Character {
    private:
        const int maxLoad;
        Strategy* strategy;

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

};