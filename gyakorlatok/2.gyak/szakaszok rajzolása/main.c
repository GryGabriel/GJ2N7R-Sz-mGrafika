#include "draw_line.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(int argc, char* argv[]){
    //Változók deklarálása, szükségesek értékadása
    SDL_Window* window;
    SDL_Renderer* renderer;
    int error_code;
    int window_size=640; //MAX_LINE_COUNT
    
    int color_pos[6][4]; //6 szín, mindegyikhez egy kezdőpont(x,y), egy szélesség és egy magasság
    int colors[6][3];
    SDL_Event event;
    
    bool running;
    Line line[window_size];
    int line_count;
    int line_demo[2];
    int default_color[3]; //Az alapértelmezett szín(fehér) RGB kódjait tartalmazza a program elején, futás közben a kiválasztott színét.
    int point_track;
    
    
    //SDL inicializálása
    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if(error_code != 0){
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }

    //SDL ablak létrehozása
    window = SDL_CreateWindow("SDL program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size, window_size, 0);
    
    //SDL ablak megjelenítése
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer==NULL){
        printf("[ERROR] Monitor cannot be created: %s\n", SDL_GetError());
        exit(1);
    }
    
    //Színpaletta létrehozása
    fill_color_palette(window_size,colors,color_pos,6,4);
    
    
    
    //Értékadások
    running=true;
    point_track=0;
    line_count=0;
    default_color[0]=255;
    default_color[1]=255;
    default_color[2]=255;
    
    //Program futása
    while (running) {
        //Színpaletta kirajzolása:
        draw_color_palette(renderer,colors,color_pos,6,4);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&line_demo[0],&line_demo[1]);
                    if(line_demo[1] <= 100){ //Megvizsgálja, hogy a rajzoló felületen kívül(a színpaletta területén) történt-e a kattintás
                        for(int i=0;i<6;i++){ //A for cikluson belül megvizsgálja, hogy színre történt-e kattintás
                            if(line_demo[0] >= color_pos[i][0] && line_demo[0] <= color_pos[i][0] + color_pos[i][2] && line_demo[1] >= color_pos[i][1] && line_demo[1] <= color_pos[i][1] + color_pos[i][3]){
                                default_color[0]=colors[i][0];
                                default_color[1]=colors[i][1];
                                default_color[2]=colors[i][2];
                                break;
                            }
                        }
                    }else if(line_demo[1] > 100){ //A rajzfelületen történt kattintás.
                        switch(point_track){
                            case 0:
                                line[line_count].x1=line_demo[0];
                                line[line_count].x2=line_demo[1];
                                
                                point_track++;
                                break;
                            case 1:
                                line[line_count].y1=line_demo[0];
                                line[line_count].y2=line_demo[1];
                                
                                line[line_count].color.R=default_color[0];
                                line[line_count].color.G=default_color[1];
                                line[line_count].color.B=default_color[2];
                                line_count++;
                                point_track--;
                                break;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                case SDL_SCANCODE_Q:
                    running = false;
                    break;
                case SDL_QUIT:
                    running= false;
                    break;
                    
            }
        }
        for(int i=0;i<line_count;i++){
            //szakasz
            SDL_SetRenderDrawColor(renderer,line[i].color.R,line[i].color.G,line[i].color.B,0);
            SDL_RenderDrawLine(renderer,line[i].x1,line[i].x2,line[i].y1,line[i].y2);
            SDL_RenderPresent(renderer);
            
            //téglalap /Még nem teljesen működőképes
            /*SDL_Rect rectangle;
        
            if(line[i].x1 < line[i].y1){
                if(line[i].x2 > line[i].y2){
                    rectangle.x=line[i].x1;
                    rectangle.y=line[i].y2;
                    rectangle.w=abs(line[i].y1-line[i].x1);
                    rectangle.h=abs(line[i].y2-line[i].x2);
                    
                }else if(line[i].x2 < line[i].y2){
                    rectangle.x=line[i].x1;
                    rectangle.y=line[i].x2;
                    rectangle.w=abs(line[i].y1-line[i].x1);
                    rectangle.h=abs(line[i].y2-line[i].x2);
                }
            }else if(line[i].x1 > line[i].x2){
                if(line[i].x2 > line[i].y2){
                    rectangle.x=line[i].y1;
                    rectangle.y=line[i].y2;
                    rectangle.w=abs(line[i].y1-line[i].x1);
                    rectangle.h=abs(line[i].y2-line[i].x2);
                }else if(line[i].x2 < line[i].y2){
                    rectangle.x=line[i].y1;
                    rectangle.y=line[i].x2;
                    rectangle.w=abs(line[i].y1-line[i].x1);
                    rectangle.h=abs(line[i].y2-line[i].x2);
                }
            }
            SDL_SetRenderDrawColor(renderer,line[i].color.R,line[i].color.G,line[i].color.B,0);
            SDL_RenderFillRect(renderer,&rectangle);*/
        }
    }
    
    //A megjelenítő és az ablak megszüntetése, kilépés
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
