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
     SDL_SetRenderDrawColor(r,
         std::min(250, (int)f.tracked_fishes.size()*25),
         std::max(0, 250 - (int)f.tracked_fishes.size()*25),
         std::max(0, 250 - (int)f.tracked_fishes.size()*25),255);
    SDL_FRect rect = {(float)f.x*FISH_SIZE,(float)f.y*FISH_SIZE,FISH_SIZE,FISH_SIZE};
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
        f.close_fishes.clear();
        f.tracked_fishes.clear();

        for (Fish &other_f: fishes) {
            if (&f == &other_f) continue;

            UnitVector dist_vec = UnitVector(f.x,f.y,other_f.x,other_f.y);
            if (  dist_vec.len < f.tracking_dist && (abs(f.dir_vec.deg - dist_vec.deg) < f.view_shift)) {
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

    SDL_Texture* canvas = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(r);

    for (int i = 0; i<1000 ; i++) {
        fishes.push_back(Fish(getRand(0,SCREEN_WIDTH/FISH_SIZE),getRand(0,SCREEN_HEIGHT/FISH_SIZE),getRand(0,360)));
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
            //if (f.x< 0 || f.y < 0 || f.x > 600 || f.y > 400) { f.x = 300; f.y = 200;}
            drawFish(r, f);
        }

        SDL_SetRenderTarget(r, NULL);
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_RenderTexture(r, canvas, NULL , NULL);

        SDL_RenderPresent(r);
        SDL_Delay(0);
    }

    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}

