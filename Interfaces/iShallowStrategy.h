# pragma once
# include "iStrategy.h"

class iShallowStrategy : public iStrategy {
    protected:
        int getRoomQuota() {
            // return random(2, 4);
            return 1; // TODO: Quitar tras finalizar debug
        }

        bool isDepthLimit() { // Nota: Diseño ideado a ser future-proof si aumenta tunel depth-limit
            int tunnelHeight = tunnelEntrance->get_height();
            if (tunnelHeight > 3) { // Medium to large tunnel
                int currentHeight = currentChamber->get_height();
                tunnelHeight /= 2; // Half height
                return currentHeight <= (++tunnelHeight);
            } else { // For small tunnels
                return false;
            }
        }
};