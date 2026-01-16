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
    float padding = 128;
    float scroll_val = 0;
    float scroll_max_val;
    float scroll_size = 16;
    float scroll_range = SCREEN_WIDTH - SEA_WIDTH - padding*2;
    std::string description;

    Slider(SDL_Renderer *r, SDL_Texture* font_bmp, double y, float scroll_max_val, std::string description ): r(r), font_bmp(font_bmp), y(y), scroll_max_val(scroll_max_val), description(description) {}
    void drawSlider();
    void drawScroll();
    float getScrollPos(){return SEA_WIDTH + padding + (scroll_val)*scroll_range;}
    void setScrollPos(float pos);
    void drawVal();
    void drawDescription();
};


#endif //SEASIM_SLIDER_H