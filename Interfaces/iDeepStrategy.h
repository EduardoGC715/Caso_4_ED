# pragma once
# include "iStrategy.h"

class iDeepStrategy : public iStrategy {
    protected:
        int getRoomQuota() {
            return random(3, 5);
        }

    public:
        void searchChamber() {
            printf("Explores tunnel deeply\n");
        }
};