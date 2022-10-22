#include <iostream>

#ifndef CHAMBER
#define CHAMBER

class Chamber {
private:
    int m_minerals;
    int m_distance;
    int m_potential;
    int m_chamber_ID;
    bool m_transitable;
public:
    Chamber(int t_minerals, int t_distance, int t_chamber_ID) {
        m_minerals = t_minerals;
        m_distance = t_distance;
        m_potential=t_minerals*t_distance;
        m_chamber_ID=t_chamber_ID;
        m_transitable=true;
    }

    int get_minerals() {
        return m_minerals;
    }
    void set_minerals(int t_minerals){
        m_minerals = t_minerals;
    }

    int get_distance() {
        return m_distance;
    }
    void set_distance(int t_distance){
        m_distance = t_distance;
    }

    int get_potential() {
        return m_potential;
    }
    void update_potential(){
        m_potential=m_minerals*m_distance;
    }

    int get_ID() {
        return m_chamber_ID;
    }

    void mine(){
        m_minerals--;
    }

    bool is_transitable() {
        return m_transitable;
    }

    void update_transitable(){
        if(m_minerals==0){
            m_transitable=false;
        }
    }
};
#endif
