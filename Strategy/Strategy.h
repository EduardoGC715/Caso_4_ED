# pragma once
# include <string>

using namespace std;

enum State {
    UNAVAILABLE = 0,
    SEARCH      = 1,
    UNDERGROUND = 2,
    MINING      = 3,
    RETRIEVE    = 4
};

class Strategy {
    public:
        string name;

        virtual void searchTunnel() = 0;
        virtual void searchChamber() = 0;
        virtual void mineChamber() = 0;
        virtual void retrieveMineral() = 0;

};
