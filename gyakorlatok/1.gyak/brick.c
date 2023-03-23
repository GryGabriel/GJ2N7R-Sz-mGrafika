#include "brick.h"
#include <stdio.h>

void set_size(Brick* brick){
    int count=0,check;
    do{
        check=0;
        switch (count){
        case 0:
                printf("What length should the %d. edge be?\n", count+1);
                check=scanf("%lf",&brick->a);
                while(getchar() != '\n');
                if(check==1) count++;
                break;
        case 1:
                printf("What length should the %d. edge be?\n", count+1);
                check=scanf("%lf",&brick->b);
                while(getchar() != '\n');
                if(check==1) count++;
                break;
        case 2:
                printf("What length should the %d. edge be?\n", count+1);
                check=scanf("%lf",&brick->c);
                while(getchar() != '\n');
                if(check==1) count++;
                break;
        }
    }while(count<3);
}

double calc_volume(Brick brick){
    return brick.a*brick.b*brick.c;
}

double calc_surface(Brick brick){
    return 2*brick.a*brick.b+2*brick.a*brick.c+2*brick.b*brick.c;
}

int check_square_sides(Brick brick){
    int sum=0;
    if(brick.a==brick.b) sum++;
    if(brick.a==brick.c) sum++;
    if(brick.b==brick.c) sum++;
    return 2*sum;
}
