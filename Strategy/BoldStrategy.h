# pragma once
# include "../Interfaces/iDeepExpedition.h"

class BoldStrategy : public iDeepExpedition {
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