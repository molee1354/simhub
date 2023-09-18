#include <SDL.h>
#include <stdio.h>
#include <unistd.h>

#include "SDL_render.h"
#include "SDL_video.h"
#include "fluid.h"
#include "sim.input"

#define CELL_SIZE 5

#define WINDOW_WIDTH NUM_X*CELL_SIZE + 4*CELL_SIZE
#define WINDOW_HEIGHT NUM_Y*CELL_SIZE + 4*CELL_SIZE

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

static void draw_grid(Fluid* fluid) {
    int n = fluid->numY;
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            SDL_Rect point;
            point.x = i * CELL_SIZE + (2*CELL_SIZE);
            point.y = j * CELL_SIZE + (2*CELL_SIZE);
            point.w = (int)(CELL_SIZE*.8);
            point.h = (int)(CELL_SIZE*.8);

            double smoke = fluid->m[i*n + j];

            if (smoke == 0.) {
                SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);
            } else {
                SDL_SetRenderDrawColor(renderer,
                        smoke*255,
                        smoke*255,
                        smoke*255, 255);
            }
            SDL_RenderFillRect(renderer, &point);
        }
    }
}

static void initialState(Fluid* fluid, double inVel) {
    int n = fluid->numY;
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            double s = 1.; // fluid
            if (i == 0 || j == 0 || j == fluid->numY-1) s = 0.; // solid

            fluid->s[i*n + j] = s;
            if (i == 1) {
                fluid->u[i*n + j] = inVel;
            }
        }
    }

    double pipeHeight = .1 * fluid->numY;
    double minJ = floor(.5 * fluid->numY - .5*pipeHeight);
    double maxJ = floor(.5 * fluid->numY + .5*pipeHeight);

    for (int j = minJ; j < maxJ; j++) {
        fluid->m[j] = 0.;
    }
    
}


int main(int argc, char* argv[]) {
    Fluid* fluid = initFluid(DENSITY, NUM_X, NUM_Y, DEF_H);
    initialState(fluid, 5.);

    window = SDL_CreateWindow("Eulerian Fluid",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            WINDOW_WIDTH, 
            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_Delay(16);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        simulate(fluid, DT, GRAVITY, NUM_ITER);
        draw_grid(fluid);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
