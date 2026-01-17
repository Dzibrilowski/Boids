//
// Created by user on 16.01.2026.
//

#ifndef SEASIM_SLIDER_H
#define SEASIM_SLIDER_H
#include <SDL3/SDL_render.h>

#include "Utils.h"


class Slider {
public:
    SDL_Renderer *r;
    SDL_Texture* font_bmp;
    double y;
    double width = SCREEN_WIDTH - SEA_WIDTH;
    float height = CHAR_SIZE * 2;
    float range_bold = 4;

    float scroll_range = 200;
    float padding_right = CHAR_SIZE * 11;
    float padding_left = UI_WIDTH - padding_right - scroll_range;

    float scroll_val;
    float scroll_max_val;
    float scroll_size = 16;
    std::string description;

    int* val_to_change;

    Slider(SDL_Renderer *r, SDL_Texture* font_bmp, double y, int* val_to_change, float scroll_max_val, std::string description ):
    r(r), font_bmp(font_bmp), y(y), val_to_change(val_to_change), scroll_max_val(scroll_max_val), description(description) {scroll_val = *val_to_change/scroll_max_val;}
    void drawSlider();
    void drawScroll();
    float getScrollPos(){return SEA_WIDTH + padding_left + (scroll_val)*scroll_range;}
    void setScrollPos(float pos);
    void drawVal();
    void drawDescription();
};


#endif //SEASIM_SLIDER_H