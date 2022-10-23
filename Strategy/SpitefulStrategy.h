# pragma once
# include "../Interfaces/iShallowStrategy.h"

class SpitefulStrategy : public iShallowStrategy {
    protected:
        bool decide_mining() {
        // High probability at low depth, decreases as depth increases
            int tunnelHeight = tunnelEntrance->get_height();
            int currentHeight = currentChamber->get_height();
            int boundary = (10*currentHeight)/tunnelHeight;
            int chance = random(0,boundary);

            // Showcase print
            // printf("\nChance %d | Boundary %d\n", chance, boundary);
            return chance;
        }

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
};