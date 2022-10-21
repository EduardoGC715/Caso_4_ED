# pragma once
# include "../Interfaces/iDeepStrategy.h"

class BoldStrategy : public iDeepStrategy {
    public:
        BoldStrategy() {
            name = "Spelunker: Chunk mining, Deep scouting, Early return";
        }

        iStrategy* clone() {
            return new BoldStrategy;
        }

        void mineChamber() {
            printf("Spelunker mining placeholder\n");
        }

        void retrieveMineral() {
            printf("Spelunker retrieval placeholder\n");
        }
};