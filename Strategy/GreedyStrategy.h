# pragma once
# include "../Interfaces/iDeepStrategy.h"

class GreedyStrategy : public iDeepStrategy {
    protected:
        bool decide_mining() {
        // Flat chance increase given by depth
            int maxHeight = tunnelEntrance->get_height();
            int currentHeight = currentChamber->get_height();
            int threshold = 100*(maxHeight-currentHeight) / maxHeight;
            int chance = random(1,100);

            // Showcase print
            // printf("\nChance %d | Threshold %d\n", chance, threshold);
            return (chance <= threshold);
        }

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
};