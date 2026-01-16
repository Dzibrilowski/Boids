//
// Created by user on 16.01.2026.
//

#include "Utils.h"

#include <string>
#include <SDL3/SDL_render.h>

void drawLetter(SDL_Renderer *r , SDL_Texture* font_bmp, int ascii , double x, double y) {
    if (ascii >= 97 && ascii <= 122) ascii-=32;

    int src_x;
    int src_y;
    if (ascii >= 65 && ascii <= 90) {
        src_x = ascii - 65;
        src_y = 0;
    }
    else if (ascii >= 48 && ascii <= 57) {
        src_x = ascii - 48 + 1;
        src_y = 1;
    }
    else if ( ascii == 32) {
        src_x = 0;
        src_y = 1;
    }
    else if ( ascii == 58) {
        src_x = 13;
        src_y = 1;
    }
    else if (ascii == 47) {
        src_x = 14;
        src_y = 1;
    }
    else {
        src_x = 12;
        src_y = 1;
    }
    SDL_FRect src = {(float)src_x*16,(float)src_y*16,16,16 };
    SDL_FRect dst = {(float)x + SEA_WIDTH,(float)y,CHAR_SIZE,CHAR_SIZE};

    SDL_RenderTexture(r,font_bmp,&src,&dst);
}

void drawText(SDL_Renderer *r , SDL_Texture* font_bmp, std::string text , double x, double y) {
    int char_num = 0;
    for (char letter: text) {
        drawLetter(r,font_bmp,letter,x + char_num*CHAR_SIZE,y);
        char_num++;

    }
}