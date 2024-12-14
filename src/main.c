#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "math/vector.h"

const int N_POINTS = 9 * 9 * 9;
vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

vec3_t camera_position = {0, 0, - 5};

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
    for (int i = 0; i < N_POINTS; ++i) {
        vec3_t point = cube_points[i];

        point.z -= camera_position.z;

        vec2_t project_point = project(point);
        projected_points[i] = project_point;

    }
}

void render(void) {
    draw_dots(0xFF, 10);

    for (int i = 0; i < N_POINTS; ++i) {
        vec2_t  projected_point = projected_points[i];
        draw_rect(
                projected_point.x + (window_width / 2),
                projected_point.y + (window_height / 2),
                4,
                4,
                0xFFFFFF00);
    }

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
