#include <iostream>

#ifndef POINT
#define POINT

class Point {
private:
    int m_x;
    int m_y;

public:
    Point(int t_x, int t_y){
        m_x=t_x;
        m_y=t_y;
    }

    int get_x(){
        return m_x;
    }
    int get_y(){
        return m_y;
    }

    bool compare(int t_x, int t_y){
        if (t_x==m_x && t_y==m_y){
            return true;
        }
        return false;
    }
};

#endif
