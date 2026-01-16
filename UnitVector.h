//
// Created by user on 08.01.2026.
//

#ifndef SEASIM_VECTOR_H
#define SEASIM_VECTOR_H


class UnitVector {
private:
    void normalizeDeg(double unnormalized_deg);
public:
    double x, y, deg;
    double len = 1;
    UnitVector(double degree);
    UnitVector(double x1, double y1, double x2, double y2, bool on_torus = false);

    void setVector(double new_deg);
    void setVector(double x1, double y1, double x2, double y2, bool on_torus = false);
};


#endif //SEASIM_VECTOR_H