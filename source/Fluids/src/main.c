#include <SDL.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window (600x480)
    const int width = 600;
    const int height = 480;
    SDL_Window* window = SDL_CreateWindow("SDL Moving Square",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Set the background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Create a rectangle for the blue square
    SDL_Rect rect;
    rect.x = 250; // X-coordinate of the top-left corner
    rect.y = 190; // Y-coordinate of the top-left corner
    rect.w = 100; // Width of the rectangle
    rect.h = 100; // Height of the rectangle

    // Main loop
    int quit = 0;

    double squareX = (double)rect.x;
    double dx = .05;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer with the black background color
        SDL_RenderClear(renderer);

        // Set the color to blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        // Draw the blue square at the updated position
        squareX += dx;
        rect.x = (int)squareX;
        if (rect.x > width-rect.w || rect.x < 0) {
            dx *= -1.;
        }
        SDL_RenderFillRect(renderer, &rect);

        // Render the scene
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }

    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
