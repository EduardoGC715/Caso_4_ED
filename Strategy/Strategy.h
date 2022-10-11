# pragma once
# include <string>

using namespace std;

class Strategy {
    public:
        string name;

        virtual void execute() = 0;
        virtual void searchTunnel() = 0;
        virtual void searchChamber() = 0;
};
