# pragma once
# include "../Interfaces/iShallowExpedition.h"

class SpitefulStrategy : public iShallowExpedition {
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