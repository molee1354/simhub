#include <SDL.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "SDL_render.h"
#include "SDL_video.h"
#include "fluid.h"
#include "sim.input"

#define CELL_SIZE 5

#define WINDOW_WIDTH NUM_X*CELL_SIZE + 4*CELL_SIZE
#define WINDOW_HEIGHT NUM_Y*CELL_SIZE + 4*CELL_SIZE

#define OBSTACLE_RADIUS 50
#define OBSTACLE_COLOR 211, 211, 211

#define BACKGROUND_COLOR 255, 255, 255
#define BLACK 0, 0, 0

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

// Obstacle
bool drawing = false;

static int obstacle_x = WINDOW_WIDTH/2;
static int obstacle_y = WINDOW_HEIGHT/2;

void drawObstacle(SDL_Renderer* render, int x, int y) {
    for (int dy = -OBSTACLE_RADIUS; dy <= OBSTACLE_RADIUS; dy++) {
        for (int dx = -OBSTACLE_RADIUS; dx <= OBSTACLE_RADIUS; dx++) {
            int dist = dx * dx + dy * dy;
            
            if (dist >= (OBSTACLE_RADIUS - 5) * (OBSTACLE_RADIUS - 5) &&
                dist <= OBSTACLE_RADIUS * OBSTACLE_RADIUS) {
                SDL_SetRenderDrawColor(render, BLACK, 255);
                SDL_RenderDrawPoint(render, x + dx, y + dy);
            } else if (dist > OBSTACLE_RADIUS * OBSTACLE_RADIUS) {
                SDL_SetRenderDrawColor(render, BACKGROUND_COLOR, 255);
                SDL_RenderDrawPoint(render, x + dx, y + dy);
            } else {
                SDL_SetRenderDrawColor(render, OBSTACLE_COLOR, 255); // Black outline
                SDL_RenderDrawPoint(render, x + dx, y + dy);
            }
        }
    }
}

static void drawGrid(Fluid* fluid) {
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

static bool initGraphics() {
    window = SDL_CreateWindow("Eulerian Fluid",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            WINDOW_WIDTH, 
            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return false;
    }
    return true;
}

static void mainLoop(Fluid* fluid) {
    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    drawing = true;
                    obstacle_x = event.button.x;
                    obstacle_y = event.button.y;
                }
            } 

        }
        SDL_Delay(16);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        simulate(fluid, DT, GRAVITY, NUM_ITER);
        drawGrid(fluid);
        drawObstacle(renderer, obstacle_x, obstacle_y);

        SDL_RenderPresent(renderer);
    }
}
int main(int argc, char* argv[]) {
    Fluid* fluid = initFluid(DENSITY, NUM_X, NUM_Y, DEF_H);
    initialState(fluid, 5.);

    if (!initGraphics()) {
        SDL_Quit();
    }

    mainLoop(fluid);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
