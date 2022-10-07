#include <iostream>

#ifndef CHAMBER
#define CHAMBER
//Tree Node
class Chamber {
private:
    int minerals;
    int distance_from_root;
    int potential;
    int cham_ID;
public:
    Chamber() {
        minerals=0;
        distance_from_root=0;
        potential=0;
        cham_ID=0;
    }

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
