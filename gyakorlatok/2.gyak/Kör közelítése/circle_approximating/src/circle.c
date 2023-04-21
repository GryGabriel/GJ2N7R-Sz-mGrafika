#include "circle.h"

#include <math.h>
#include <SDL.h>

void set_circle_data(Circle* circle, double x, double y, double radius)
{
	circle->x = x;
	circle->y = y;
	if (radius > 0.0) {
		circle->radius = radius;
	} else {
		circle->radius = NAN;
	}
}

double calc_circle_area(const Circle* circle)
{
	return circle->radius * circle->radius * M_PI;
}


/**
 * Basic solution, no added argument
 * */
void approx_circle(SDL_Renderer* renderer, int x, int y, int r){
    int first_x, first_y, second_x, second_y;

    first_x = x + r;
    first_y = y;
    float angle = M_PI / 180.0;
    for(float i = 0; i < 2.0 * M_PI; i += angle){
    	second_x = x + r * cos(i);
    	second_y = y + r * sin(i);

    	SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);

    	first_x = second_x;
    	first_y = second_y;
   	}
}

/**
 * Solution with given steps
 * */
void approx_circle_given_steps(SDL_Renderer* renderer, int x, int y, int r, float steps){
	int first_x,first_y,second_x,second_y;

	first_x = x + r;
	first_y = y;
	float angle = (2.0 * M_PI) / steps;
	for(float i = 0;i < 2.0 * M_PI + angle; i += angle){  
		second_x = x + r * cos(i);
		second_y = y + r * sin(i);

		SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);

		first_x = second_x;
		first_y = second_y;
	}
}

/**
 * Solution with given angle
 * */
void approx_circle_given_angle(SDL_Renderer* renderer, int x, int y, int r, float angle){
	int first_x,first_y,second_x,second_y;

	first_x = x + r;
	first_y = y;
	angle *= M_PI/180.0;
	for(float i = 0;i <= 2.0 * M_PI /* + angle */; i += angle){ // "+ angle" makes it work with large angles like 90 or 120
		second_x = x + r * cos(i);
		second_y = y + r * sin(i);
		
		SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);

		first_x = second_x;
		first_y = second_y;
	}
}

/**
 * Solution with given line length
 * */
void approx_circle_given_length(SDL_Renderer* renderer, int x, int y, int r, float line_length){
	int first_x,first_y,second_x,second_y;

	first_x = x + r;
	first_y = y;
	float angle = acos( -(pow(line_length,2) - 2*pow(r,2)) / (2*pow(r,2)));

	for(float i = 0;i < 2.0 * M_PI ; i += angle){
		second_x = x + r * cos(i);
		second_y = y + r * sin(i);

		SDL_RenderDrawLine(renderer,first_x,first_y,second_x,second_y);
		

		first_x = second_x;
		first_y = second_y;
	}
}
