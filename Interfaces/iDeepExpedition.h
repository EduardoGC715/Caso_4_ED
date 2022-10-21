# pragma once
# include "iStrategy.h"

class iDeepExpedition : public iStrategy {
    public:
        void searchChamber() {
            printf("Explores deep level chambers\n");
        }
};