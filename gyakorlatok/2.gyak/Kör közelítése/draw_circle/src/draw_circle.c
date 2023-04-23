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

void draw_right_scale_arrow(SDL_Renderer* renderer, int arrow[3]){
    int first_x,first_y,second_x,second_y;

	first_x = arrow[0] + arrow[2];
	first_y = arrow[1];
	float angle = M_PI/180.0 * 120;
	for(float i = 0;i <= 2.0 * M_PI + angle; i += angle){ // "+ angle" makes it work with large angles like 90 or 120
		second_x = arrow[0] + arrow[2] * cos(i);
		second_y = arrow[1] + arrow[2] * sin(i);
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);

		first_x = second_x;
		first_y = second_y;
	}
}

void draw_left_scale_arrow(SDL_Renderer* renderer, int arrow[3]){
    int first_x,first_y,second_x,second_y;

	first_x = arrow[0] - arrow[2];
	first_y = arrow[1];
	float angle = M_PI/180.0 * 120;
	for(float i = 0;i <= 2.0 * M_PI + angle; i += angle){ // "+ angle" makes it work with large angles like 90 or 120
		second_x = arrow[0] - arrow[2] * cos(i);
		second_y = arrow[1] + arrow[2] * sin(i);
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);

		first_x = second_x;
		first_y = second_y;
	}
}