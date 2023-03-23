#ifndef BRICK_H
#define BRICK_H

//A brick object with it's 3 edges
typedef struct Brick {
    double a;
    double b;
    double c;
}Brick;

//Sets the length of edges in a brick object
void set_size(Brick* brick);

//Calculates the volume of a brick
double calc_volume(Brick brick);

//Calculates the surface of a brick
double calc_surface(Brick brick);

//Checks whether any side of the brick is square-shaped
int check_square_sides(Brick brick);

#endif
