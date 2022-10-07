#include <iostream>

#ifndef CHAMBER
#define CHAMBER
//Tree Node
class Chamber {
private:
    //nodo
    Chamber *parent;
    Chamber *next_lower;
    Chamber *next_higher;
    //datos
    int minerals;
    int distance_from_root;
    int potential;
    int height;
    int cham_ID;
public:
    Chamber() {
        //nodo
        parent = nullptr;
        next_lower = nullptr;
        next_higher = nullptr;
        //datos
        minerals=0;
        distance_from_root=0;
        potential=0;
        height=0;
        cham_ID=0;
    }

    Chamber(int pminerals, int pdistance, int pcham_ID) {
        parent = nullptr;
        next_lower = nullptr;
        next_higher = nullptr;

        minerals = pminerals;
        distance_from_root = pdistance;
        potential=pminerals*pdistance;
        height=1;
        cham_ID=pcham_ID;
    }

    void Set_Parent(Chamber *parent_cam) {
        parent = parent_cam;
    }
    void Set_Next_Lower(Chamber *plower_cam) {
        next_lower = plower_cam;
    }
    void Set_Next_Higher(Chamber *phigher_cam) {
        next_higher = phigher_cam;
    }
    Chamber* Get_Parent() {
        return parent;
    }
    Chamber* Get_Next_Lower() {
        return next_lower;
    }
    Chamber* Get_Next_Higher() {
        return next_higher;
    }

    int Set_Height(int pheight) {
        height=pheight;
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
    int Get_Height() {
        return height;
    }
    int Get_ID() {
        return cham_ID;
    }
};
#endif
