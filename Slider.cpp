//
// Created by user on 16.01.2026.
//

#include "Slider.h"

#include <algorithm>

void Slider::drawSlider() {
    SDL_SetRenderDrawColor(r,255,255,0,255);
    SDL_FRect border = {SEA_WIDTH,(float)y,UI_WIDTH,height};
    SDL_RenderRect(r,&border);

    SDL_SetRenderDrawColor(r,200,200,200,255);
    SDL_FRect range = {
        SEA_WIDTH+ padding,
        (float)y + (height-range_bold)/2,
        UI_WIDTH - 2*padding,
        (float)range_bold};
    SDL_RenderFillRect(r,&range);

    drawScroll();
    drawVal();
    drawDescription();

}
void Slider::drawScroll() {
    SDL_SetRenderDrawColor(r,0,0,0,255);
    SDL_FRect range = {
        getScrollPos() - scroll_size/2,
        (float)y + (height-scroll_size)/2,
        scroll_size,
        scroll_size};
    SDL_RenderFillRect(r,&range);
}
void Slider::setScrollPos(float pos) {
    float start_x = SEA_WIDTH + padding;
    float end_x = start_x + scroll_range;
    pos = std::max(std::min(pos, end_x), start_x);
    scroll_val = (pos - start_x)/ scroll_range;
}

void Slider::drawVal() {
    drawText(r, font_bmp, std::to_string((int)(scroll_val * scroll_max_val))+"/"+std::to_string((int)scroll_max_val),
        UI_WIDTH - padding + CHAR_SIZE,(float)y + (height-scroll_size)/2);
}

void Slider::drawDescription() {
    drawText(r, font_bmp, description,
        padding - (description.length()+1)*CHAR_SIZE,(float)y + (height-scroll_size)/2);

}



