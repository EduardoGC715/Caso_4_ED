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
            //  Los dos if cubren todos los casos:
            //      1. Minero lleno inventario -> RETRIEVE to entrance
            //      2. Minero colapso el tunel -> Retreat & SEARCH other chamber
            //      3. Minero lleno inventario y colapso tunel -> RETRIEVE to entrance
            if (*load != *maxLoad) { // Inventario disponible
                if (currentChamber->get_data()->is_transitable()) {
                    currentChamber->get_data()->mine();
                    ++(*load);
                    message = ("Mines the chamber");
                } else { // Abandona tunel colapsado
                    state = UNDERGROUND;
                    discard_chamber();
                    retreat_chamber();
                    int chamberID = currentChamber->get_data()->get_ID();
                    message = ("Collapsed the chamber! Returned to chamber #" + to_string(chamberID));
                }
            } else {
                state = RETRIEVE;
                message = ("Filled their inventory");
            }
            sleep(1);
        }
};