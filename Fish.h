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
    double close_dist = 5;
    double tracking_dist = 60;
    double move_shift = 25;
    double view_shift = 50;
    double speed = 1;
    std::vector<Fish*> tracked_fishes;
    std::vector<Fish*> close_fishes;


    Fish(double x, double y, double dir): x(x), y(y), dir_vec(UnitVector(dir)){}
    void move();


};


#endif //SEASIM_FISH_H