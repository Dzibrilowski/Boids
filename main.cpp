#include <ctime>
#include <iostream>
#include <vector>
#include "SDL3/SDL.h"
#include "cmath"
#include "Fish.h"
#include <algorithm>

#include "Slider.h"
#include "Utils.h"

std::vector<Fish> fishes;


void drawFish(SDL_Renderer *r, Fish &f) {
    double focus_f = std::min((double)f.tracked_fishes.size() / f.focus_num,1.0);
     SDL_SetRenderDrawColor(r,
         (int)(fish_r*(1 - focus_f)+focus_r*focus_f),
         (int)(fish_g*(1 - focus_f)+focus_g*focus_f),
         (int)(fish_b*(1 - focus_f)+focus_b*focus_f),
          255);
    SDL_FRect rect = {(float)f.x*FISH_SIZE,(float)f.y*FISH_SIZE,FISH_SIZE,FISH_SIZE};
    SDL_RenderFillRect(r, &rect);

    // SDL_SetRenderDrawColor(r,200,200,0,255);
    // UnitVector topBorder = UnitVector(f.dir_vec.deg + f.view_shift);
    // UnitVector bottomBorder = UnitVector(f.dir_vec.deg - f.view_shift);
    // SDL_RenderLine(r,f.x*FISH_SIZE+FISH_SIZE/2,f.y*FISH_SIZE+FISH_SIZE/2,f.x*FISH_SIZE+ topBorder.x*f.tracking_dist,f.y*FISH_SIZE+ topBorder.y*f.tracking_dist);
    // SDL_RenderLine(r,f.x*FISH_SIZE+FISH_SIZE/2,f.y*FISH_SIZE+FISH_SIZE/2,f.x*FISH_SIZE+ bottomBorder.x*f.tracking_dist,f.y*FISH_SIZE+ bottomBorder.y*f.tracking_dist);
}

void update_fish_tracking() {
    for (Fish &f: fishes) {
        f.close_fishes.clear();
        f.tracked_fishes.clear();

        for (Fish &other_f: fishes) {
            if (&f == &other_f) continue;

            UnitVector dist_vec = UnitVector(f.x,f.y,other_f.x,other_f.y, true);
            double angle_diff = abs(f.dir_vec.deg - dist_vec.deg);
            if (angle_diff > 180) angle_diff = 360 - angle_diff;
            if (  dist_vec.len < f.tracking_dist && angle_diff < f.view_shift) {
                f.tracked_fishes.push_back(&other_f);

            }
            if (dist_vec.len < f.close_dist ) {
                f.close_fishes.push_back(&other_f);
            }
        }
    }
}


int main() {
    srand(time(nullptr));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* w = SDL_CreateWindow(
        "sea",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
        );
    SDL_Renderer* r = SDL_CreateRenderer(w,NULL);

    SDL_Texture* sea_texture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SEA_WIDTH, SEA_HEIGHT);
    SDL_SetTextureBlendMode(sea_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(r);



    SDL_Surface* font_surface = SDL_LoadBMP("czcionka.bmp");

    const SDL_PixelFormatDetails* details = SDL_GetPixelFormatDetails(font_surface->format);
    uint32_t color_key = SDL_MapRGB(details, NULL, 255, 0, 255);
    SDL_SetSurfaceColorKey(font_surface, true, color_key);

    SDL_Texture* font_texture = SDL_CreateTextureFromSurface(r,font_surface);
    SDL_SetTextureBlendMode(font_texture, SDL_BLENDMODE_BLEND);

    float first_slider_y = CHAR_SIZE*2;
    std::vector<Slider> sliders;
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 2,&Fish::tracking_dist,200,"track dist"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 4,&Fish::close_dist,100,"close dist"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 6,&Fish::move_shift,180,"move shift"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 8,&Fish::view_shift,180,"view shift"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 10,&Fish::focus_num,100,"focus num"));

    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 14,&fish_r,255,"fish r"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 16,&fish_g,255,"fish g"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 18,&fish_b,255,"fish b"));

    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 22,&focus_r,255,"focus r"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 24,&focus_g,255,"focus g"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 26,&focus_b,255,"focus b"));


    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 30,&Fish::speed,10,"speed"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 32,&blur,255,"blur"));
    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 34,&delay,100,"delay ms"));

    sliders.push_back(Slider(r, font_texture,first_slider_y + CHAR_SIZE * 38,&fish_num,2000,"fishes num"));


    for (int i = 0; i<fish_num ; i++) {
        fishes.push_back(Fish(getRand(0,SEA_WIDTH/FISH_SIZE),getRand(0,SEA_HEIGHT/FISH_SIZE),getRand(0,360)));
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
            if (e.type == SDL_EVENT_MOUSE_MOTION) {
                if (e.motion.state && SDL_BUTTON_LMASK) {
                    float mouse_x = e.motion.x;
                float mouse_y = e.motion.y;
                for (Slider &s: sliders) {
                    if (mouse_x >= SEA_WIDTH + s.padding_left && mouse_x <= SCREEN_WIDTH - s.padding_right &&
                        mouse_y >= s.y  && mouse_y <= s.y + s.height ) {
                        s.setScrollPos(mouse_x);
                    }
                }
                }

            }

        }

        SDL_SetRenderTarget(r, sea_texture);

        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(r,0,0,0,blur);
        SDL_RenderFillRect(r,NULL);

        if (fish_num < fishes.size()) {
            for (int i = 0; i<fishes.size()-fish_num; i++) {
                fishes.pop_back();
            }
        }
        if (fish_num > fishes.size()) {
            for (int i = 0; i<fish_num - fishes.size(); i++) {
                fishes.push_back(Fish(getRand(0,SEA_WIDTH/FISH_SIZE),getRand(0,SEA_HEIGHT/FISH_SIZE),getRand(0,360)));
            }
        }

        update_fish_tracking();
        for (Fish &f: fishes) {
            f.move();
            drawFish(r, f);
        }


        SDL_SetRenderTarget(r, NULL);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_FRect sea_rect = {0,0,SEA_WIDTH,SEA_HEIGHT};
        SDL_RenderTexture(r, sea_texture, NULL , &sea_rect);

        // ui

        SDL_FRect ui_rect = {SEA_WIDTH,0,UI_WIDTH,UI_HEIGHT};
        SDL_SetRenderDrawColor(r, 40, 40, 50, 255);
        SDL_RenderFillRect(r, &ui_rect);

        for (Slider &s : sliders) {
            s.drawSlider();
        }

        SDL_RenderPresent(r);
        SDL_Delay(delay);
    }
    SDL_DestroyTexture(font_texture);
    SDL_DestroyTexture(sea_texture);
    SDL_DestroySurface(font_surface);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}

