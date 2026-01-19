//
// Created by user on 08.01.2026.
//

#include "Fish.h"

#include <cmath>

#include "Utils.h"

int Fish::close_dist = 5;
int Fish::tracking_dist = 60;
int Fish::move_shift = 25;
int Fish::view_shift = 50;
int Fish::speed = 1;
int Fish::focus_num = 4;
int Fish::close_factor = 2;

void Fish::move() {

    if (tracked_fishes.size() > 0) {
        double dir_x = 0;
        double dir_y = 0;
        double pos_x = 0;
        double pos_y = 0;
        for (Fish* f : tracked_fishes) {
            dir_x += f->dir_vec.x;
            dir_y += f->dir_vec.y;

            UnitVector pos_vec = UnitVector(x,y,f->x,f->y, true);

            pos_x += pos_vec.x * pos_vec.len;
            pos_y += pos_vec.y * pos_vec.len;
        }
        dir_x /= tracked_fishes.size();
        dir_y /= tracked_fishes.size();
        UnitVector dir_v = UnitVector(0,0,dir_x,dir_y);

        pos_x /= tracked_fishes.size();
        pos_y /= tracked_fishes.size();
        UnitVector pos_v = UnitVector(0,0,pos_x,pos_y);

        if (close_fishes.size() > 0) {
            double esc_x = 0;
            double esc_y = 0;
            for (Fish* f : close_fishes) {
                UnitVector esc_vec = UnitVector(x,y,f->x,f->y, true);

                esc_x -= esc_vec.x * esc_vec.len;
                esc_y -= esc_vec.y * esc_vec.len;
            }
            esc_x /= close_fishes.size();
            esc_y /= close_fishes.size();
            UnitVector esc_v = UnitVector(0,0,esc_x,esc_y);


                dir_vec.setVector(0,0,dir_v.x+pos_v.x+esc_v.x*close_factor,
                    dir_v.y+pos_v.y+esc_v.y* close_factor);
        }

        else {
            UnitVector rand_v = UnitVector(getRand(dir_vec.deg-move_shift, dir_vec.deg+move_shift));
            double focus_factor = std::min((double)focus_num/(double)tracked_fishes.size(),1.0);
            dir_vec.setVector(0,0,dir_v.x+pos_v.x + focus_factor*rand_v.x,dir_v.y+pos_v.y + focus_factor *rand_v.y);

        }
    }

    else {dir_vec.setVector(getRand(dir_vec.deg-move_shift, dir_vec.deg+move_shift));}

    x += dir_vec.x * speed;
    y += dir_vec.y * speed;


    x = fmod(x+MAP_WIDTH, MAP_WIDTH);
    y = fmod(y+MAP_HEIGHT, MAP_HEIGHT);


}