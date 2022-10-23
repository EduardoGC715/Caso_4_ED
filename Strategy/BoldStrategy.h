# pragma once
# include "../Interfaces/iDeepStrategy.h"

class BoldStrategy : public iDeepStrategy {
    protected:
        bool decide_mining() {
        // Very low probability at low depth, high at max depth
            int maxHeight = tunnelEntrance->get_height();
            int currentHeight = currentChamber->get_height();
            int threshold = 100*(maxHeight-currentHeight) / (maxHeight*currentHeight);
            int chance = random(1,100);

            // Showcase print
            // printf("\nChance %d | Threshold %d\n", chance, threshold);
            return (chance <= threshold);
            
        }

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
};