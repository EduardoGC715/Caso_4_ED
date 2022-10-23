# pragma once
# include "iStrategy.h"

class iDeepStrategy : public iStrategy {
    protected:
        int getRoomQuota() {
            // return random(3, 5);
            return 1; // TODO: Quitar tras finalizar debug
        }

        bool isDepthLimit() { // Establece cualquier nodo hoja como limite
            int currentHeight = currentChamber->get_height();
            return currentHeight == 1;
        }
};