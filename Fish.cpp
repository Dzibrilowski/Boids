//
// Created by user on 08.01.2026.
//

#include "Fish.h"

#include <cmath>

#include "Utils.h"

void Fish::move() {

    if (tracked_fishes.size() > 0) {
        double dir_x = 0;
        double dir_y = 0;
        double pos_x = 0;
        double pos_y = 0;
        double dist_tf = 0;
        for (Fish* f : tracked_fishes) {
            dist_tf = std::sqrt(f->x*f->x + f->y*f->y);
            dir_x += f->dir_vec.x;
            dir_y += f->dir_vec.y;
            pos_x += f->x;
            pos_y += f->y;
        }
        dir_x /= tracked_fishes.size();
        dir_y /= tracked_fishes.size();
        UnitVector dir_v = UnitVector(0,0,dir_x,dir_y);

        pos_x /= tracked_fishes.size();
        pos_y /= tracked_fishes.size();
        UnitVector pos_v = UnitVector(x,y,pos_x,pos_y);

        if (too_close_fishes.size() > 0) {
            double esc_x = 0;
            double esc_y = 0;
            double dist_tcf;
            for (Fish* f : too_close_fishes) {
                dist_tcf = std::sqrt(f->x*f->x + f->y*f->y);

                esc_x += f->x;
                esc_y += f->y;
            }
            esc_x /= too_close_fishes.size();
            esc_y /= too_close_fishes.size();
            UnitVector esc_v = UnitVector(x,y,esc_x,esc_y);

            // if (is_crit_dist_reached) {
            //     dir_vec.setVector(0,0,-esc_v.x,-esc_v.y);
            //     is_crit_dist_reached = false;
            // }
           // else

            //if (tracked_fishes.size() < 5) {
                // rand_factor_x = getRand(-shift/tracked_fishes.size(), shift/tracked_fishes.size());
                // rand_factor_y = getRand(-shift/tracked_fishes.size(), shift/tracked_fishes.size());
            //}

                dir_vec.setVector(0,0,dir_v.x+pos_v.x-esc_v.x*view.length/short_dist,
                    dir_v.y+pos_v.y-esc_v.y* view.length/short_dist);
        }

        else {
            UnitVector rand_v = UnitVector(getRand(dir_vec.deg-shift, dir_vec.deg+shift));

            dir_vec.setVector(0,0,dir_v.x+pos_v.x + 4*rand_v.x/tracked_fishes.size(),dir_v.y+pos_v.y + 4*rand_v.y/tracked_fishes.size());

        }


    // dir_vec.setVector(getRand(dir_vec.deg-shift, dir_vec.deg+shift));
    }

    else {dir_vec.setVector(getRand(dir_vec.deg-shift, dir_vec.deg+shift));}

    x += dir_vec.x * speed;
    y += dir_vec.y * speed;
}