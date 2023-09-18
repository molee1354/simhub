#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "fluid.h"
#include "sim.input"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 780

#define OBSTACLE_RADIUS 10
#define OBSTACLE_COLOR 211, 211, 211

#define WHITE 255, 255, 255
#define BLACK 0, 0, 0

// Obstacle
bool drawing = false;

static int obstacle_x = WINDOW_WIDTH/2;
static int obstacle_y = WINDOW_HEIGHT/2;

double simHeight;
double cScale;
double simWidth;
int cellSize;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

static double cX(int x) {
    return (double)x * cScale;
}

static double cY(int y) {
    return WINDOW_HEIGHT - (double)y * cScale;
}

static void setObstacle(Fluid* fluid, int x, int y) {
    double vx = (x - obstacle_x) / DT;
    double vy = (y - obstacle_y) / DT;

    obstacle_x = x;
    obstacle_y = y;

    int n = fluid->numY;
    int r = OBSTACLE_RADIUS;

    for (int i = 1; i < fluid->numX-2; i++) {
        for (int j = 1; j < fluid->numY-2; j++) {
            fluid->s[i*n + j] = 1.;

            double dx = ((double)i + .5) * fluid->h - x;
            double dy = ((double)j + .5) * fluid->h - y;
            double rad2 = (double)(r*r);

            if (dx*dx + dy*dy < rad2*2) {
                puts("yes");
                fluid->s[i*n + j] = 0.;
                fluid->m[i*n + j] = 1.;

                fluid->u[i*n + j] = vx;
                fluid->u[(i+1)*n + j] = vx;
                fluid->v[i*n + j] = vy;
                fluid->v[i*n + j+1] = vy;
            }
        }
    }

}

static void draw(Fluid* fluid) {
    int n = fluid->numY;
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            SDL_Rect point;
            point.x = i * cellSize;
            point.y = j * cellSize;
            point.w = (int)(cellSize*.9);
            point.h = (int)(cellSize*.9);

            double smoke = fluid->m[i*n + j];

            SDL_SetRenderDrawColor(renderer,
                                   smoke*255,
                                   smoke*255,
                                   smoke*255,
                                   255);
            if (fluid->s[i*n + j] == 0.) {
                SDL_SetRenderDrawColor(renderer, BLACK, 255);
            }
            SDL_RenderFillRect(renderer, &point);
        }
    }

    for (int dy = -OBSTACLE_RADIUS; dy <= OBSTACLE_RADIUS; dy++) {
        for (int dx = -OBSTACLE_RADIUS; dx <= OBSTACLE_RADIUS; dx++) {
            int dist = dx * dx + dy * dy;
            
            if (dist >= (OBSTACLE_RADIUS - 5) * (OBSTACLE_RADIUS - 5) &&
                dist <= OBSTACLE_RADIUS * OBSTACLE_RADIUS) {
                SDL_SetRenderDrawColor(renderer, BLACK, 255);
                SDL_RenderDrawPoint(renderer, obstacle_x + dx, obstacle_y + dy);
            } else if (dist > OBSTACLE_RADIUS * OBSTACLE_RADIUS) {
                continue;
            } else {
                SDL_SetRenderDrawColor(renderer, OBSTACLE_COLOR, 255); // Black outline
                SDL_RenderDrawPoint(renderer, obstacle_x + dx, obstacle_y + dy);
            }
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
    double minJ = (int)floor(.5 * fluid->numY - .5*pipeHeight);
    double maxJ = (int)floor(.5 * fluid->numY + .5*pipeHeight);

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
//                    obstacle_x = event.button.x;
//                    obstacle_y = event.button.y;
                    setObstacle(fluid, event.button.x, event.button.y);
                }
            } 

        }
        SDL_Delay(16);

        SDL_SetRenderDrawColor(renderer, WHITE, 255);
        SDL_RenderClear(renderer);

        simulate(fluid, DT, GRAVITY, NUM_ITER);
//        setObstacle(fluid, obstacle_x, obstacle_y);
        draw(fluid);

        SDL_RenderPresent(renderer);
    }
}

static void initSimParam() {
    simHeight = 1.1;
    cScale = WINDOW_HEIGHT / simHeight;
    simWidth = WINDOW_WIDTH / cScale;
}

int main(int argc, char* argv[]) {
    initSimParam();

    double domainHeight = 1.;
    double domainWidth = domainHeight / simHeight * simWidth;
    double res = 100.;
    double h = domainHeight / res;

    int numX = floor(domainWidth/h);
    int numY = floor(domainHeight/h);

    cellSize = 0.99*WINDOW_WIDTH / numX;

    printf("        numX = %d\n", numX);
    printf("        numY = %d\n", numY);
    printf("    cellSize = %d\n", cellSize);
    printf(" domainWidth = %g\n", domainWidth);
    printf("domainHeight = %g\n", domainHeight);

    Fluid* fluid = initFluid(DENSITY, numX, numY, h);
    initialState(fluid, IN_VEL);

    if (!initGraphics()) {
        SDL_Quit();
    }

    mainLoop(fluid);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
