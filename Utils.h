//
// Created by user on 09.01.2026.
//

#ifndef SEASIM_UTILS_H
#define SEASIM_UTILS_H

#include <string>
#include <SDL3/SDL_render.h>

#include "cstdlib"


void drawLetter(SDL_Renderer *r , SDL_Texture* font_bmp, int ascii , double x, double y);
void drawText(SDL_Renderer *r , SDL_Texture* font_bmp, std::string text , double x, double y);

inline double getRand(double min, double max) {
    return  (double)rand()/RAND_MAX * (max-min) + min;
}
inline double getClosestWay(double num, double length) {
    if ( num > length/2) num-= length;
    else if ( num < -length/2) num+= length;
    return num;
}
static inline const int SCREEN_WIDTH = 1400;
static inline const int SCREEN_HEIGHT = 800;
static inline const int SEA_WIDTH = SCREEN_HEIGHT;
static inline const int SEA_HEIGHT = SCREEN_HEIGHT;
static inline const int UI_WIDTH = SCREEN_WIDTH - SEA_WIDTH;
static inline const int UI_HEIGHT = SCREEN_HEIGHT;
static inline const int MAP_WIDTH = 4000;
static inline const int MAP_HEIGHT = 4000;
static inline const int CHAR_SIZE = 16;


static int fish_r = 200;
static int fish_g = 0;
static int fish_b = 0;

static int focus_r = 10;
static int focus_g = 200;
static int focus_b = 200;

static int blur = 15;
static int delay = 5;

static int fish_num  = 500;
static float fish_size = 1;

static float center_x = SEA_WIDTH/fish_size/2;
static float center_y = SEA_HEIGHT/fish_size/2;

#endif //SEASIM_UTILS_H