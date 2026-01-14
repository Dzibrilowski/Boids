//
// Created by user on 08.01.2026.
//

#ifndef SEASIM_FISH_H
#define SEASIM_FISH_H
#include <vector>

#include "UnitVector.h"


class Fish {
    struct View {
        double length;
        double shift;
    };
public:
    View view;
    double short_dist = 5;
    double crit_dist = 5;
    bool is_crit_dist_reached = false;
    double x, y;
    UnitVector dir_vec;
    double shift;
    double speed;
    std::vector<Fish*> tracked_fishes;
    std::vector<Fish*> too_close_fishes;


    Fish(double x, double y, double dir, double shift, double view_shift,  double speed = 1): x(x), y(y), dir_vec(UnitVector(dir)), shift(shift), speed(speed){ view.shift = view_shift; view.length = 40;}
    void move();


};


#endif //SEASIM_FISH_H