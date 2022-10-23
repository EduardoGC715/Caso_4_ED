# pragma once
# include "../Interfaces/iShallowStrategy.h"

class CarefulStrategy : public iShallowStrategy {
    protected:
        bool decide_mining() { // Flat 66.67% chance :|
            int chance = random(0,2);

            // Showcase print
            // printf("\nChance %d\n", chance);
            return chance;
        }

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
};