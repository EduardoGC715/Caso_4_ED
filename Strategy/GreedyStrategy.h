# pragma once
# include "../Interfaces/iDeepStrategy.h"

class GreedyStrategy : public iDeepStrategy {
    public:
        GreedyStrategy(/* args */) {
            name = "Gold Digger: Full mining, Deep scouting, Early return";
        }

        iStrategy* clone() {
            return new GreedyStrategy;
        }

        void mineChamber() {
            printf("Gold digger mining placeholder\n");
        }

        void retrieveMineral() {
            printf("Gold digger retrieval placeholder\n");
        }
};