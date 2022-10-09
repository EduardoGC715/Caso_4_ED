#include <iostream>

#ifndef CHAMBER
#define CHAMBER

class Chamber {
private:
    int m_minerals;
    int m_distance;
    int m_potential;
    int m_chamber_ID;
public:
    Chamber(int t_minerals, int t_distance, int t_chamber_ID) {
        m_minerals = t_minerals;
        m_distance = t_distance;
        m_potential=t_minerals*t_distance;
        m_chamber_ID=t_chamber_ID;
    }

    int get_minerals() {
        return m_minerals;
    }
    int get_distance() {
        return m_distance;
    }
    int get_potential() {
        return m_potential;
    }
    int get_ID() {
        return m_chamber_ID;
    }
};
#endif
