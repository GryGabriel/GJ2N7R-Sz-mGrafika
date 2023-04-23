#ifndef DRAW_CIRCLE_H
#define DRAW_CIRCLE_H

#include <SDL.h>

typedef struct Circle{
    int x;
    int y;
    int radius;
}Circle;

/**
 * Initialize the circle
*/
void init_circle(Circle *circle, int x, int y, int radius);

void init_rectangle(SDL_Rect *rectangle, int *values);

void save_circle(int (*circles)[6], int *circle_count, int x, int y, int radius, int current_color[3]);

void draw_circles(SDL_Renderer* renderer, int (*circles)[6], int circle_count);

void draw_right_scale_arrow(SDL_Renderer* renderer, int arrow[3]);

void draw_left_scale_arrow(SDL_Renderer* renderer, int arrow[3]);

#endif //DRAW_CIRCLE_H