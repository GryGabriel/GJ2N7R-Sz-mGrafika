#ifndef DRAW_LINE_H
#define DRAW_LINE_H
#include <SDL.h>

typedef struct Color{
    int R;
    int G;
    int B;
}Color;

typedef struct Line{
    int x1;
    int x2;
    int y1;
    int y2;
    Color color;
}Line;

void fill_color_palette(int window_size, int (*colors)[3], int (*color_pos)[4], int rows, int columns);

void draw_color_palette(SDL_Renderer* renderer, int (*colors)[3], int (*color_pos)[4], int rows, int columns);

#endif
