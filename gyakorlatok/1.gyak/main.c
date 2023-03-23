#include "brick.h"

#include <stdio.h>

int main(){
    Brick brick;
    set_size(&brick);
    
    printf("The volume of the edge is: %.3lf\n", calc_volume(brick));
    
    printf("The surface of the edge is: %.3lf\n", calc_surface(brick));
    
    printf("The brick contains %d square-shaped sides.\n", check_square_sides(brick));
    return 0;
}
