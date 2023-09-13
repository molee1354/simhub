#include <SDL.h>
#include <time.h>

#include "gol_commonincl.h"

#if NCOLS > 200 || NROWS > 100
#define CELL_SIZE 5
#else
#define CELL_SIZE 10
#endif

#define WINDOW_WIDTH NCOLS*CELL_SIZE + 4*CELL_SIZE
#define WINDOW_HEIGHT NROWS*CELL_SIZE + 4*CELL_SIZE

#define BLACK 0, 0, 0, 255
#define WHITE 211, 211, 211, 255

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

static void draw_grid(Board* board) {
    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLS; j++) {
            SDL_Rect rect;
            rect.x = j * CELL_SIZE + (2*CELL_SIZE);
            rect.y = i * CELL_SIZE + (2*CELL_SIZE);
            rect.w = (int)(CELL_SIZE*.8);
            rect.h = (int)(CELL_SIZE*.8);

            if (board->boardMatrix[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, BLACK);
            } else {
                SDL_SetRenderDrawColor(renderer, WHITE);
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void render() {
    Board* board = makeRandomBoard(NROWS, NCOLS);
    void (*nextBoard)(Board*);

    if (NCOLS > 512 && NROWS <=512) {
        puts("using openmp.");
        nextBoard = generateNext_mp;
    } else if (NCOLS > 512 && NROWS > 512) {
        puts("using nested openmp.");
        nextBoard = generateNext_mp2;
    } else {
        nextBoard = generateNext;
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
    }

    window = SDL_CreateWindow("Game of Life",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        (WINDOW_WIDTH < 1900) ? WINDOW_WIDTH : 1900,
        (WINDOW_HEIGHT < 1000) ? WINDOW_HEIGHT : 1000,
        SDL_WINDOW_SHOWN);

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

        SDL_Delay(32);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        nextBoard(board);
        draw_grid(board);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
