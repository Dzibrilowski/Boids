//
// Created by user on 08.01.2026.
//

#include "UnitVector.h"
#include <cmath>
#include <iostream>

UnitVector::UnitVector(double degree) : deg(degree) {
    normalizeDeg(deg);
    x = std::cos(deg * M_PI/180);
    y = std::sin(deg * M_PI/180);
}
UnitVector::UnitVector(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    len = sqrt(dx*dx + dy*dy);

    deg = atan2(dy , dx) * 180 / M_PI;
    deg = fmod(deg,360);

    x = dx/len;
    y = dy/len;
}


void UnitVector::setVector(double new_deg) {
    normalizeDeg(new_deg);

    x = std::cos(deg * M_PI/180);
    y = std::sin(deg * M_PI/180);
}

void UnitVector::setVector(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    len = sqrt(dx*dx + dy*dy);

    deg = atan2(dy , dx) * 180 / M_PI;
    deg = fmod(deg,360);

    x = dx/len;
    y = dy/len;
}

void UnitVector::normalizeDeg(double unnormalized_deg) {
    unnormalized_deg = fmod(unnormalized_deg,360);
    if (unnormalized_deg<0) unnormalized_deg += 360;
    deg = unnormalized_deg;

}



