//
// Created by Mike on 08.12.2024.
//

#include "display.h"

int window_width = 800;
int window_height = 600;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;

uint32_t *color_buffer = NULL;

bool init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error with init SDL. \n");
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

    window_width = display_mode.w;
    window_height = display_mode.h;

    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              window_width,
                              window_height,
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

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
            color_buffer_texture,
            NULL,
            color_buffer,
            (int) (window_width * sizeof(uint32_t)));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {

    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void draw_grid(uint32_t color, int space) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if (x % space == 0 || y % space == 0) {
                color_buffer[y * window_width + x] = color;
            }
        }
    }
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int current_x = x + i;
            int current_y = y + j;

            color_buffer[(window_width * current_y) + current_x] = color;
        }
    }
}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}