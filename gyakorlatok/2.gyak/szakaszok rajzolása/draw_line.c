#include "draw_line.h"
#include <SDL.h>

void fill_color_palette(int window_size, int (*colors)[3], int (*color_pos)[4], int rows, int columns){
    int width_per_color=(window_size-100)/rows;
    for(int i=0;i<rows;i++){
        color_pos[i][0]=50+(i*width_per_color)+(i*2);
        color_pos[i][1]=50;
        color_pos[i][2]=width_per_color;
        color_pos[i][3]=50;
    }
    colors[0][0]=255;
    colors[0][1]=255;
    colors[0][2]=255;
    
    colors[1][0]=255;
    colors[1][1]=255;
    colors[1][2]=0;
    
    colors[2][0]=255;
    colors[2][1]=0;
    colors[2][2]=0;
    
    colors[3][0]=0;
    colors[3][1]=255;
    colors[3][2]=0;
    
    colors[4][0]=0;
    colors[4][1]=0;
    colors[4][2]=255;
    
    colors[5][0]=0;
    colors[5][1]=0;
    colors[5][2]=0;
}

void draw_color_palette(SDL_Renderer* renderer, int (*colors)[3], int (*color_pos)[4], int rows, int columns){
    SDL_Rect rectangle;
    for(int i=0;i<rows;i++){
        rectangle.x=color_pos[i][0];
        rectangle.y=color_pos[i][1];
        rectangle.w=color_pos[i][2];
        rectangle.h=color_pos[i][3];
        
        //Színek kirajzolása
        SDL_SetRenderDrawColor(renderer,colors[i][0],colors[i][1],colors[i][2],0);
        SDL_RenderFillRect(renderer,&rectangle);
        //Keretek kirajzolása
        SDL_SetRenderDrawColor(renderer,255,255,255,0);
        SDL_RenderDrawRect(renderer,&rectangle);
        SDL_RenderPresent(renderer);
    }
}

