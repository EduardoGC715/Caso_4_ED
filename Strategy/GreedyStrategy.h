# pragma once
# include "DeepExpedition.h"

class GreedyStrategy : public DeepExpedition {
    public:
        GreedyStrategy(/* args */) {
            name = "Gold Digger: Full mining, Deep scouting, Early return";
        }

        void mineChamber() {
            printf("Gold digger mining\n");
        }

        void retrieveMineral() {
            printf("Gold digger retrieval\n");
        }
};