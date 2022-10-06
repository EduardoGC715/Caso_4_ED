#include <iostream>

#ifndef CAMARA
#define CAMARA

class Camara {
private:
    //nodo
    Camara *parent;
    Camara *next_lower;
    Camara *next_higher;
    //datos
    int minerals;
    int distance;
    int potential;
    int id;
public:
    Camara() {
        //nodo
        parent = nullptr;
        next_lower = nullptr;
        next_higher = nullptr;
        //datos
        minerals=0;
        distance=0;
        potential=0;
        id=0;
    }

    Camara(int pminerals,int pdistance,int pid) {
        parent = nullptr;
        next_lower = nullptr;
        next_higher = nullptr;

        minerals = pminerals;
        distance = pdistance;
        potential=pminerals*pdistance;
        id=pid;
    }

    void set_parent(Camara *parent_cam) {
        parent = parent_cam;
    }
    void set_next_lower(Camara *plower_cam) {
        next_lower = plower_cam;
    }
    void set_next_higher(Camara *phigher_cam) {
        next_higher = phigher_cam;
    }
    Camara* get_parent() {
        return parent;
    }
    Camara* get_next_lower() {
        return next_lower;
    }
    Camara* get_next_hiher() {
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
        return id;
    }
};

#endif
