# pragma once
# include "ShallowExpedition.h"

class CarefulStrategy : public ShallowExpedition {
    public:
        CarefulStrategy() {
            name = "Cautious: Chunk mining, Surface scouting, Fill inventory";
        }

        void mineChamber() {
            printf("Mines carefully\n");
        }

        void retrieveMineral() {
            printf("Retrieves carefully\n");
        }
};