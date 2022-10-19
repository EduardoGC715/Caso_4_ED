#include <iostream>

#ifndef POINT
#define POINT

class Point {
private:
    int m_x;
    int m_y;

public:
    Point(int t_x, int t_y){
        m_x = t_x;
        m_y = t_y;
    }

    int get_x(){
        return m_x;
    }
    void set_x(int t_x){
        m_x = t_x;
    }

    int get_y(){
        return m_y;
    }
    void set_y(int t_y){
        m_y = t_y;
    }

    void set_point(Point* t_point){
        m_x=t_point->get_x();
        m_y=t_point->get_y();
    }

    bool compare_point(Point* t_point){
        if (t_point->get_x()==m_x && t_point->get_y()==m_y){
            return true;
        }
        return false;
    }

    bool compare_coords(int t_x, int t_y){
        if (t_x==m_x && t_y==m_y){
            return true;
        }
        return false;
    }
};

#endif
