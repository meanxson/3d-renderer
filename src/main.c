#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;

bool init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error with init SDL. \n");
        return false;
    }
    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,
                              600,
                              SDL_WINDOW_BORDERLESS);

    if (!window) {
        fprintf(stderr, "Error with creating Window. \n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        fprintf(stderr, "Error with creating Renderer. \n");
        return false;
    }

    return true;
}

int main(void) {
    is_running = init_window();
}
