#include <iostream>

#ifndef CHAMBER
#define CHAMBER

class Chamber {
private:
    int minerals;
    int distance_from_root;
    int potential;
    int cham_ID;
public:
    Chamber(int pminerals, int pdistance, int pcham_ID) {
        minerals = pminerals;
        distance_from_root = pdistance;
        potential=pminerals*pdistance;
        cham_ID=pcham_ID;
    }

    int Get_Minerals() {
        return minerals;
    }
    int Get_Distance() {
        return distance_from_root;
    }
    int Get_Potential() {
        return potential;
    }
    int Get_ID() {
        return cham_ID;
    }
};
#endif
