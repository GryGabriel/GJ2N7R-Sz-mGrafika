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

int check_coordinates(int mouse_x, int mouse_y, int x1, int x2, int y1, int y2);

void save_circle(int (*circles)[6], int *circle_count, int x, int y, int radius, int current_color[3]);

void draw_circles(SDL_Renderer* renderer, int (*circles)[6], int circle_count);

void move_circle(SDL_Renderer* renderer, int (*circles)[6], int circle_counter, int mouse_x, int mouse_y);


#endif //DRAW_CIRCLE_H