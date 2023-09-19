#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "fluid.h"
#include "fluids_commonincl.h"

#define OBSTACLE_COLOR 211, 211, 211

#define WHITE 255, 255, 255
#define BLACK 0, 0, 0

// Obstacle
bool drawing = false;

static int obstacle_x = WINDOW_WIDTH/2;
static int obstacle_y = WINDOW_HEIGHT/2;

static double domainHeight;
static double domainWidth;
static double simHeight;
static double cScale;
static double simWidth;
static int cellSize;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {
    int red;
    int green;
    int blue;
} RGB;

static void initSimParam() {
    simHeight = 1.1;
    cScale = WINDOW_HEIGHT / simHeight;
    simWidth = WINDOW_WIDTH / cScale;

    domainHeight = 1.;
    domainWidth = domainHeight / simHeight * simWidth;
}

static double cX(int x) {
    return (double)x * cScale;
}

static double cY(int y) {
    return WINDOW_HEIGHT - (double)y * cScale;
}

static void setObstacle(Fluid* fluid, int x, int y, bool reset) {
    double vx = 0.;
    double vy = 0.;

    if (!reset) {
        vx = (x - obstacle_x) / DT;
        vy = (y - obstacle_y) / DT;
    }

    obstacle_x = x;
    obstacle_y = y;

    int n = fluid->numY;
    double obsRad = OBSTACLE_RADIUS;

    for (int i = 1; i < fluid->numX-2; i++) {
        for (int j = 1; j < fluid->numY-2; j++) {
            fluid->s[i*n + j] = 1.;

            double dx = ((double)i + .5) * fluid->h - ((double)x/WINDOW_WIDTH)*domainWidth;
            double dy = ((double)j + .5) * fluid->h - ((double)y/WINDOW_HEIGHT)*domainHeight;
            double rad2 = (double)(obsRad*obsRad);

            if (dx*dx + dy*dy < rad2) {
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

static RGB getColor(double value, double minVal, double maxVal) {
    RGB out;
    double red, green, blue;
    
    value = findMin( findMax(value, minVal), maxVal - 0.0001);
    double diff = maxVal - minVal;

    value = diff == 0. ? .5 : (value - minVal) / diff;

    double m = .25;
    int num = (int)floor(value/m);

    double s = (value - (double)num*m) / m;
    
    switch (num) {
        case 0: {
            red = 0.;
            green = s;
            blue = 1.;
            break;
        }
        case 1: {
            red = 0.;
            green = 1.;
            blue = 1. - s;
            break;
        }
        case 2: {
            red = s;
            green = 1.;
            blue = 0.;
            break;
        }
        case 3: {
            red = 1.;
            green = 1. - s;
            blue = 0.;
            break;
        }
    }
    out.red = (int)(255*red);
    out.green = (int)(255*green);
    out.blue = (int)(255*blue);
    return out;
}

static void draw(Fluid* fluid) {
    SDL_RenderClear(renderer);
    int n = fluid->numY;

    double minP = fluid->p[0];
    double maxP = fluid->p[0];

    for (int i = 0; i < fluid->numCells; i++) {
        minP = findMin(minP, fluid->p[i]);
        maxP = findMax(maxP, fluid->p[i]);
    }

    RGB rgb = {255, 255, 255};
    for (int i = 0; i < fluid->numX; i++) {
        for (int j = 0; j < fluid->numY; j++) {
            SDL_Rect point;
            point.x = i * cellSize;
            point.y = j * cellSize;
            point.w = cellSize;
            point.h = cellSize;

            if (PRESSURE == 1) {
                double pressure = fluid->p[i*n + j];
                double smoke = fluid->m[i*n + j];
                rgb = getColor(pressure, minP, maxP);

                if (SMOKE == 1) {
                    rgb.red = findMax(0., (double)rgb.red - 255.*smoke);
                    rgb.green = findMax(0., (double)rgb.green - 255.*smoke);
                    rgb.blue = findMax(0., (double)rgb.blue - 255.*smoke);
                }
            } else if (SMOKE == 1) {
                double smoke = fluid->m[i*n + j];

                rgb.red = smoke*255.;
                rgb.green = smoke*255.;
                rgb.blue = smoke*255.;
            } else if (fluid->s[i*n + j] == 0.) {
                rgb.red = 0;
                rgb.green = 0;
                rgb.blue = 0;
            }
            SDL_SetRenderDrawColor(renderer,
                    rgb.red,
                    rgb.green,
                    rgb.blue,
                    255);
            SDL_RenderFillRect(renderer, &point);
        }
    }

    // draw obstacle
    double obsRad = (OBSTACLE_RADIUS + fluid->h) * cScale;
    for (int yy = -obsRad; yy <= obsRad; yy++) {
        for (int xx = -obsRad; xx <= obsRad; xx++) {
            int dist = xx * xx + yy * yy;
            
            if (dist >= (obsRad - 4) * (obsRad - 4) &&
                dist <= obsRad * obsRad) {
                SDL_SetRenderDrawColor(renderer, BLACK, 255);
                SDL_RenderDrawPoint(renderer,
                        obstacle_x + xx,
                        obstacle_y + yy);
            } else if (dist > obsRad * obsRad) {
                continue;
            } else {
                SDL_SetRenderDrawColor(renderer, OBSTACLE_COLOR, 255); // Black outline
                SDL_RenderDrawPoint(renderer,
                        obstacle_x + xx,
                        obstacle_y + yy);
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

    double pipeHeight = INLET_HEIGHT * (double)(fluid->numY);
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
                    setObstacle(fluid, event.button.x, event.button.y, true);
                }
            } 

        }
        SDL_Delay(16);

        simulate(fluid, DT, GRAVITY, NUM_ITER);
        setObstacle(fluid, obstacle_x, obstacle_y, false);
        draw(fluid);

        SDL_RenderPresent(renderer);
    }
}

void render() {
    initSimParam();

    double res = 100.;
    double h = domainHeight / res;
    
    int numX = floor(domainWidth/h);
    int numY = floor(domainHeight/h);

    cellSize = WINDOW_WIDTH / numX;

    printf("\tFluid Density (kg/m^3) : %g\n", DENSITY);
    printf("\t  Inlet Velocity (m/s) : %g\n", INLET_VEL);
    printf("\t       Gravity (m/s^2) : %g\n", GRAVITY);


    Fluid* fluid = initFluid(DENSITY, numX, numY, h);
    initialState(fluid, INLET_VEL);

    if (!initGraphics()) {
        SDL_Quit();
    }

    mainLoop(fluid);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
