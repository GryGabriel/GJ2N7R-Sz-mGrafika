#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>

/**
 * Data of a circle object in Descartes coordinate system
 */
typedef struct Circle
{
	double x;
	double y;
	double radius;
} Circle;

/**
 * Set the data of the circle
 */
void set_circle_data(Circle* circle, double x, double y, double radius);

/**
 * Calculate the area of the circle.
 */
double calc_circle_area(const Circle* circle);


/**
 * Draw a circle using lines 
 **/
void approx_circle(SDL_Renderer* renderer, int x, int y, int r);

void approx_circle_given_steps(SDL_Renderer* renderer, int x, int y, int r, float steps);

void approx_circle_given_angle(SDL_Renderer* renderer, int x, int y, int r, float angle);

void approx_circle_given_length(SDL_Renderer* renderer, int x, int y, int r, float line_length);

#endif // CIRCLE_H
