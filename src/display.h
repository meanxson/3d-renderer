#ifndef INC_3D_RENDERER_DISPLAY_H
#define INC_3D_RENDERER_DISPLAY_H

#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "math/vector.h"

extern int window_width;
extern int window_height;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *color_buffer_texture;

extern uint32_t *color_buffer;


bool init_window(void);

void render_color_buffer(void);

void clear_color_buffer(uint32_t color);

void destroy_window(void);

void draw_grid(uint32_t color, int space);

void draw_rect(int x, int y, int width, int height, uint32_t color);

void draw_pixel(int x, int y, uint32_t color);

void draw_dots(uint32_t color, int space);

vec2_t project(vec3_t point);

#endif //INC_3D_RENDERER_DISPLAY_H
