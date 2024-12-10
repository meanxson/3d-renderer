#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "math/vector.h"

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];

bool is_running = false;

void setup(void) {
    color_buffer = (uint32_t *) malloc(sizeof(uint32_t) * window_width * window_height);

    color_buffer_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            window_width,
            window_height);

    int point_count = 0;

    //Start loading my array of vectors
    for (float x = -1; x <= 1; x += 0.25f) {
        for (float y = -1; y <= 1; y += 0.25f) {
            for (float z = -1; z <= 1; z += 0.25f) {
                vec3_t new_point = {.x = x, .y = y, .z = z};
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
    }
}

void update(void) {

}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_dots(0xFF, 10);

    draw_rect(20, 20, 50, 50, 0xFF);
    draw_pixel(20, 20, 0xFFFFFF00);
    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = init_window();
    setup();
    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}
