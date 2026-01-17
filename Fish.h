//
// Created by user on 08.01.2026.
//

#ifndef SEASIM_FISH_H
#define SEASIM_FISH_H
#include <vector>

#include "UnitVector.h"


class Fish {
public:
    double x, y;
    UnitVector dir_vec;
    static int close_dist;
    static int tracking_dist;
    static int move_shift;
    static int view_shift;
    static int speed;
    static int focus_num;
    std::vector<Fish*> tracked_fishes;
    std::vector<Fish*> close_fishes;


    Fish(double x, double y, double dir): x(x), y(y), dir_vec(UnitVector(dir)){}
    void move();


};


#endif //SEASIM_FISH_H