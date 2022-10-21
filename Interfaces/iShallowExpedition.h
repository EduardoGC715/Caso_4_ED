# pragma once
# include "iStrategy.h"

class iShallowExpedition : public iStrategy {
    public:
        void searchChamber() {
            printf("Explores surface level chambers\n");
        }
};