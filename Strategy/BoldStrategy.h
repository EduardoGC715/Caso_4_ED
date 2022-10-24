# pragma once
# include "../Interfaces/iDeepStrategy.h"

class BoldStrategy : public iDeepStrategy {
    protected:
        bool leaveEarly = false;
        bool isCalculated = false;
        double rate;
        int amount = 0;
        int goal = 0;

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

        void calculate_rate() {
            int maxHeight = tunnelEntrance->get_height();
            int currentHeight = currentChamber->get_height();
            rate = (0.8) * ((maxHeight-currentHeight)/(maxHeight-1));
            // Flat 80%, reduced by low depth
            // Ej. max = 5, height = 4, (0.8)*(1/4) = 0.2
            // Ej. max = 5, height = 1, (0.8)*(4/4) = 0.8
        }

        bool random_leave() {
            return ( (amount < goal*0.25) && (! random(0,9)) );
        }

    public:
        BoldStrategy() {
            name = "Spelunker: Chunk mining, Deep scouting, Early return";
        }

        iStrategy* clone() {
            return new BoldStrategy;
        }

        void mineChamber() {
            Chamber* chamber = currentChamber->get_data();
            if (! isCalculated) {
                calculate_rate();
                goal = amount = chamber->get_minerals() * rate;
                isCalculated = true;
            }
            
            bool isInventoryFull = (*load == *maxLoad);
            if (chamber->is_transitable()) {
                if (! isInventoryFull && ! leaveEarly) {
                    if (amount > 0) {
                        chamber->mine();
                        ++(*load);
                        --amount;
                        int chamberID = chamber->get_ID();
                        message = ("Mines the chamber #" + to_string(chamberID) + " [" + to_string(*load)+ "]");
                        leaveEarly = random_leave();
                    } else {
                        state = UNDERGROUND;
                        isCalculated = false;
                        message = ("Finished their mining goal (" + to_string(goal) + ") [" + to_string(*load) + "]");
                    }
                } else {
                    state = RETRIEVE;
                    message = (isInventoryFull) ? ("Filled their inventory") : ("Decided to leave early");
                    isCalculated = false;
                    leaveEarly = false;
                }
            } else if (random(0,1)) { // Restriccion: Otro minero colapso chamber
                state = UNDERGROUND;
                discard_chamber();
                isCalculated = false;
                retreat_chamber(); // chamber != currentChamber.get_data();
                int chamberID = currentChamber->get_data()->get_ID();
                message = ("The chamber collapsed! Managed returning to chamber #" + to_string(chamberID));
            } else {
                state = UNAVAILABLE;
                isCalculated = false;
                message = ("The chamber collapsed! Couldn't escape");
            }
            sleep(1);
        }
};