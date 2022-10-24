# pragma once
# include "../Interfaces/iShallowStrategy.h"

class CarefulStrategy : public iShallowStrategy {
    protected:
        bool isCalculated = false;
        double rate = 0.5;
        int amount = 0;
        int goal = 0;

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
            Chamber* chamber = currentChamber->get_data();
            if (! isCalculated) {
                goal = amount = chamber->get_minerals() * rate;
                isCalculated = true;
            }
            
            bool isInventoryFull = (*load == *maxLoad);
            if (chamber->is_transitable()) {
                if (! isInventoryFull) {
                    if (amount > 0) {
                        chamber->mine();
                        ++(*load);
                        --amount;
                        int chamberID = chamber->get_ID();
                        message = ("Mines the chamber #" + to_string(chamberID) + " [" + to_string(*load)+ "]");
                    } else {
                        state = UNDERGROUND;
                        isCalculated = false;
                        message = ("Finished their mining goal (" + to_string(goal) + ") [" + to_string(*load) + "]");
                    }
                } else {
                    state = RETRIEVE;
                    message = ("Filled their inventory");
                    isCalculated = false; // Leer nota al final
                }
            } else if (random(0,4)) { // Restriccion: Otro minero colapso chamber
                state = UNDERGROUND;
                discard_chamber();
                isCalculated = false; // Leer nota al final
                retreat_chamber(); // chamber != currentChamber.get_data();
                int chamberID = currentChamber->get_data()->get_ID();
                message = ("The chamber collapsed! Managed returning to chamber #" + to_string(chamberID));
            } else {
                state = UNAVAILABLE;
                isCalculated = false; // Leer nota al final
                message = ("The chamber collapsed! Couldn't escape");
            }
            sleep(1);
            // Nota importante:
            // Desactivar flag de calculo es importante para preparar cualquier llamada nueva
            // a este metodo, incluso en caso de que colapse el chamber. Esto porque el topo
            // tiene la posibilidad de salvarse, lo cual afectaria su siguiente mining goal
        }
};