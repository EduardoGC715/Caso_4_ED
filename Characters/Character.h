# pragma once

struct Character {
    private:
        const int maxLoad;

    public:
        int speed;
        int load;

        Character(const int pMaxLoad, int pSpeed)
        : maxLoad(pMaxLoad), speed(pSpeed), load(0)
        {}
};