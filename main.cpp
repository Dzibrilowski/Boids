#include <ctime>
#include <iostream>
#include <vector>
#include "SDL3/SDL.h"
#include "cmath"
#include "Fish.h"
#include <algorithm>
#include "Utils.h"

std::vector<Fish> fishes;


void drawFish(SDL_Renderer *r, Fish &f) {
    //if (f.tracked_fishes.size() == 0) SDL_SetRenderDrawColor(r,0,0,200,255);
     SDL_SetRenderDrawColor(r,std::min(250, (int)f.tracked_fishes.size()*50),0,std::max(0, 250 - (int)f.tracked_fishes.size()*50),255);
    SDL_FRect rect = {(float)f.x*2,(float)f.y*2,2,2};
    //if (f.x > 1200 || f.x < 0 || f.y > 800 || f.y < 0 ){f.x = 600; f.y = 400;}
    SDL_RenderFillRect(r, &rect);

    // SDL_SetRenderDrawColor(r,200,200,0,255);
    // UnitVector topBorder = UnitVector(f.dir_vec.deg + f.view.shift);
    // UnitVector bottomBorder = UnitVector(f.dir_vec.deg - f.view.shift);
    // SDL_RenderLine(r,f.x*2+1,f.y*2+1,f.x*2+ topBorder.x*f.view.length,f.y*2+ topBorder.y*f.view.length);
    // SDL_RenderLine(r,f.x*2+1,f.y*2+1,f.x*2+ bottomBorder.x*f.view.length,f.y*2+ bottomBorder.y*f.view.length);
}

void update_fish_tracking() {
    for (Fish &f: fishes) {
        for (Fish &other_f: fishes) {
            if (&f == &other_f) continue;

            bool is_tracked = false;
            for (Fish* tracked_f: f.tracked_fishes) {
                if (tracked_f == &other_f) {
                    is_tracked = true;
                    break;
                }
            }
            bool is_too_close = false;
            for (Fish* too_close_f: f.too_close_fishes) {
                if (too_close_f == &other_f) {
                    is_too_close = true;
                    break;
                }
            }

            UnitVector v = UnitVector(f.x,f.y,other_f.x,other_f.y);
            UnitVector top_border = UnitVector(f.dir_vec.deg + f.view.shift);
            UnitVector bottom_border = UnitVector(f.dir_vec.deg - f.view.shift);
            // if (v.len < 80 && (v.deg > bottom_border.deg && v.deg < top_border.deg)) {
            //     if (!is_tracked) f.tracked_fishes.push_back(&other_f);
            //
            // }
            if ( v.len >= f.short_dist && v.len < f.view.length && (abs(f.dir_vec.deg - v.deg) < f.view.shift)) {
                if (!is_tracked) f.tracked_fishes.push_back(&other_f);

            }
            else if (is_tracked) {
                auto it = std::find(f.tracked_fishes.begin(),f.tracked_fishes.end(),&other_f);
                if (it != f.tracked_fishes.end()) {
                    f.tracked_fishes.erase(it);
                }
            }

            if (v.len < f.short_dist ) {
                if (!is_too_close) f.too_close_fishes.push_back(&other_f);
            }
            else if (is_too_close) {
                auto it = std::find(f.too_close_fishes.begin(),f.too_close_fishes.end(),&other_f);
                if (it != f.too_close_fishes.end()) {
                    f.too_close_fishes.erase(it);
                }
            }

            if (v.len < f.crit_dist){ f.is_crit_dist_reached = true;}
        }
    }
}


int main() {
    srand(time(nullptr));

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* w = SDL_CreateWindow(
        "sea",
        1200,
        800,
        0
        );
    SDL_Renderer* r = SDL_CreateRenderer(w,NULL);

    SDL_Texture* canvas = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1200, 800);
    SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(r);

    for (int i = 0; i<500 ; i++) {
        fishes.push_back(Fish(getRand(0,600),getRand(0,400),getRand(0,1),22,70, .5));
    }

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_EVENT_QUIT) {
              running = false;
          }
        }

        SDL_SetRenderTarget(r, canvas);
        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(r,0,0,0,10);
        SDL_RenderFillRect(r,NULL);
        //SDL_RenderClear(r);

        update_fish_tracking();
        for (Fish &f: fishes) {
            f.move();
            if (f.x< 0 || f.y < 0 || f.x > 600 || f.y > 400) { f.x = 300; f.y = 200;}
            drawFish(r, f);
        }

        SDL_SetRenderTarget(r, NULL);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_RenderTexture(r, canvas, NULL , NULL);

        SDL_RenderPresent(r);
        SDL_Delay(5);
    }

    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}

