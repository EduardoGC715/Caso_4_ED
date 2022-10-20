# pragma once
# include "ShallowExpedition.h"

class SpitefulStrategy : public ShallowExpedition {
    public:
        SpitefulStrategy(/* args */) {
            name = "Spiteful: Full mining, Surface scouting, Fill inventory";
        }

        void mineChamber() {
            printf("Mines spitefully\n");
        }

        void retrieveMineral() {
            printf("Retrieves spitefully\n");
        }
};