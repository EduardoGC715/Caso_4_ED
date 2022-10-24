# pragma once
# include "../Interfaces/iDeepStrategy.h"

class GreedyStrategy : public iDeepStrategy {
    protected:
        bool leaveEarly = false;

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

        bool random_leave() {
            return (currentChamber->get_data()->get_minerals() == 1 && random(0,1));
        }

    public:
        GreedyStrategy(/* args */) {
            name = "Gold Digger: Full mining, Deep scouting, Early return";
        }

        iStrategy* clone() {
            return new GreedyStrategy;
        }

        void mineChamber() {
            //  El minero siempre dedice descartar la camara y regresar cuando
            //      1. Colapsa el tunel
            //      2. Llena el inventario
            //  Adicionalmente, tiene un 50% para parar de minar antes de colapsar
            Chamber* chamber = currentChamber->get_data();
            bool isInventoryFull = (*load == *maxLoad);
            if (! isInventoryFull && ! leaveEarly) {
                if (chamber->is_transitable()) {
                    chamber->mine();
                    ++(*load);
                    int chamberID = chamber->get_ID();
                    message = ("Mines the chamber #" + to_string(chamberID) + " [" + to_string(*load)+ "]");
                    leaveEarly = random_leave();
                } else if (random(0,1)) {
                    state = RETRIEVE;
                    discard_chamber();
                    retreat_chamber(); // chamber != currentChamber.get_data();
                    int chamberID = currentChamber->get_data()->get_ID();
                    message = ("The chamber collapsed! Managed returning to chamber #" + to_string(chamberID));
                } else {
                    state = UNAVAILABLE;
                    message = ("The chamber collapsed! Couldn't escape");
                }
            } else {
                state = RETRIEVE;
                discard_chamber();
                message = (isInventoryFull) ? ("Filled their inventory") : ("Decided to leave early");
                leaveEarly = false;
            }
            sleep(1);
        }
};