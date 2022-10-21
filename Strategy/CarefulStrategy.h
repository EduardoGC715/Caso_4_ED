# pragma once
# include "../Interfaces/iShallowStrategy.h"

class CarefulStrategy : public iShallowStrategy {
    public:
        CarefulStrategy() {
            name = "Cautious: Chunk mining, Surface scouting, Fill inventory";
        }

        iStrategy* clone() {
            return new CarefulStrategy;
        }

        void mineChamber() {
            printf("Cautious mining placeholder\n");
        }

        void retrieveMineral() {
            printf("Cautious retrieval placeholder\n");
        }
};