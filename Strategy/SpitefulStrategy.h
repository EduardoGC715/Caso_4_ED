# pragma once
# include "../Interfaces/iShallowStrategy.h"

class SpitefulStrategy : public iShallowStrategy {
    public:
        SpitefulStrategy(/* args */) {
            name = "Spiteful: Full mining, Surface scouting, Fill inventory";
        }

        iStrategy* clone() {
            return new SpitefulStrategy;
        }

        void mineChamber() {
            printf("Spiteful mining placeholder\n");
        }

        void retrieveMineral() {
            printf("Spiteful retrieval placeholder\n");
        }
};