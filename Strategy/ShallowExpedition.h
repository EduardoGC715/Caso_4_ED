# pragma once
# include "iStrategy.h"

class ShallowExpedition : public iStrategy {
    public:
        void searchTunnel() {
            printf("Explores surface level doors\n");
        }

        void searchChamber() {
            printf("Explores surface level chambers\n");
        }
};