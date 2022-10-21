# pragma once
# include "../Interfaces/iShallowExpedition.h"

class CarefulStrategy : public iShallowExpedition {
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