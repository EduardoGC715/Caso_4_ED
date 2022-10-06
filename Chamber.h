#include <iostream>
#ifndef CHAMBER
#define CHAMBER
//Nodo
class Chamber {
private:
    //nodo
    Chamber *parent;
    Chamber *next_lower;
    Chamber *next_higher;
    //datos
    int minerals;
    int distance;
    int potential;
    int cham_id;
public:
    Chamber() {
        //nodo
        parent = nullptr;
        next_lower = nullptr;
        next_higher = nullptr;
        //datos
        minerals=0;
        distance=0;
        potential=0;
        cham_id=0;
    }

    Chamber(int pminerals, int pdistance, int pcham_id) {
        parent = nullptr;
        next_lower = nullptr;
        next_higher = nullptr;

        minerals = pminerals;
        distance = pdistance;
        potential=pminerals*pdistance;
        cham_id=pcham_id;
    }

    void set_parent(Chamber *parent_cam) {
        parent = parent_cam;
    }
    void set_next_lower(Chamber *plower_cam) {
        next_lower = plower_cam;
    }
    void set_next_higher(Chamber *phigher_cam) {
        next_higher = phigher_cam;
    }
    Chamber* get_parent() {
        return parent;
    }
    Chamber* get_next_lower() {
        return next_lower;
    }
    Chamber* get_next_higher() {
        return next_higher;
    }

    int get_minerals() {
        return minerals;
    }
    int get_distance() {
        return distance;
    }
    int get_potential() {
        return potential;
    }
    int get_id() {
        return cham_id;
    }
};
#endif
