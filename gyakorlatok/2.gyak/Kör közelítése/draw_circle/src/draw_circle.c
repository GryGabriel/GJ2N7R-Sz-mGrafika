#include "draw_circle.h"

#include <SDL.h>

void init_circle(Circle *circle,int x, int y, int radius){
    circle->x = x;
    circle->y = y;
    circle->radius = radius;
}

void init_rectangle(SDL_Rect *rectangle, int *values){
    rectangle->x = values[0];
    rectangle->y = values[1];
    rectangle->w = values[2];
    rectangle->h = values[3];
}

int check_coordinates(int mouse_x, int mouse_y, int x1, int x2, int y1, int y2){
    if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2) 
        return 1;
    else
        return 0;
}

void save_circle(int (*circles)[6], int *circle_count, int x, int y, int radius, int current_color[3]){
    circles[*circle_count][0] = x;
    circles[*circle_count][1] = y;
    circles[*circle_count][2] = radius;
    circles[*circle_count][3] = current_color[0];
    circles[*circle_count][4] = current_color[1];
    circles[*circle_count][5] = current_color[2];
    *circle_count+=1;
}   

void draw_circles(SDL_Renderer* renderer, int (*circles)[6], int circle_count){
    for(int i = 0; i < circle_count; i++){
        int first_x, first_y, second_x, second_y;

        first_x = circles[i][0] + circles[i][2];
        first_y = circles[i][1];
        float angle = M_PI / 180.0;
        for(float j = 0; j < 2.0 * M_PI; j += angle){
            second_x = circles[i][0] + circles[i][2] * cos(j);
            second_y = circles[i][1] + circles[i][2] * sin(j);
            if(first_x > 21 && first_x < 619 && first_y > 131 && first_y < 619 &&
                second_x > 21 && second_x < 619 && second_y > 131 && second_y < 619){
                SDL_SetRenderDrawColor(renderer,circles[i][3],circles[i][4],circles[i][5],255);
                SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);
            }
            first_x = second_x;
            first_y = second_y;
        }
    }
}

void move_circle(SDL_Renderer* renderer, int (*circles)[6], int circle_counter, int mouse_x, int mouse_y){

    //for(int i = circle_counter; i >= 0; i++){
        float angle, step = M_PI / 180;
    for (angle = 0; angle <= 360; angle += 10) {
        float radians = angle * step;
        float x_point = circles[0][0] + circles[0][2] * cos(radians);
        float y_point = circles[0][1] + circles[0][2] * sin(radians);
        printf("Pont(%d, %d)\n", (int)x_point, (int)y_point);
    //}
    }
    printf("\n");
}
