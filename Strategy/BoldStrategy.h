# pragma once
# include "DeepExpedition.h"

class BoldStrategy : public DeepExpedition {
    public:
        BoldStrategy() {
            name = "Spelunker: Chunk mining, Deep scouting, Early return";
        }

        void mineChamber() {
            printf("Spelunky mining\n");
        }

        void retrieveMineral() {
            printf("Spelunky retrieval\n");
        }
};