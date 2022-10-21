# pragma once
# include "iStrategy.h"

class iShallowStrategy : public iStrategy {
    protected:
        int getRoomQuota() {
            return random(2, 4);
        }

    public:
        void searchChamber() {
            printf("Explores tunnel slightly\n");
        }
};