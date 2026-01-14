//
// Created by user on 09.01.2026.
//

#ifndef SEASIM_UTILS_H
#define SEASIM_UTILS_H

#include "cstdlib"


inline double getRand(double min, double max) {
    return  (double)rand()/RAND_MAX * (max-min) + min;
}

#endif //SEASIM_UTILS_H