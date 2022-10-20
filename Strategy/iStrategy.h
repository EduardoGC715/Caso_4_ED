# pragma once
# include <string>
# include "iExpedition.h"

using namespace std;

class iStrategy : public iExpedition {
    public:
        string name;

        virtual void mineChamber() = 0;
        virtual void retrieveMineral() = 0;
};
