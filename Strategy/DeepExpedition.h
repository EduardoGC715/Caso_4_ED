# pragma once
# include "iStrategy.h"

class DeepExpedition : public iStrategy {
    public:
        void searchTunnel() {
            printf("Explores deep level doors\n");
        }

        void searchChamber() {
            printf("Explores deep level chambers\n");
        }
};