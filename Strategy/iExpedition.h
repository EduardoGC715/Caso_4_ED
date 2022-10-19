# pragma once
# include <iostream>
// # include "../Characters/Character.h"

class iExpedition {
    public:
        virtual void searchTunnel() = 0;
        virtual void searchChamber() = 0;
};