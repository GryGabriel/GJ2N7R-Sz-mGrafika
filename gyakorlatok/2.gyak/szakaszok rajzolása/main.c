#include "draw_line.h"
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]){
    int height = 640;
    int width = 560;
    Line line[height];
    int line_count=0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    int error_code;
    SDL_Event event;
    bool running;
    int point_track;
    
    
    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if(error_code != 0){
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return error_code;
    }
    
    window = SDL_CreateWindow("SDL program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, 0);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer==NULL){
        printf("[ERROR] Monitor cannot be created: %s\n", SDL_GetError());
        exit(1);
    }
    point_track=0;
    running=true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                    //case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                    if(point_track==0){
                        point_track++;
                        SDL_GetMouseState(&line[line_count].x1,&line[line_count].x2);
                        break;
                    }else if(point_track==1){
                        point_track++;
                        SDL_GetMouseState(&line[line_count].y1,&line[line_count].y2);
                        line[line_count].color.R=255;
                        line[line_count].color.G=255;
                        line[line_count].color.B=255;
                        
                        point_track=0;
                        line_count++;
                        break;
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
            SDL_SetRenderDrawColor(renderer,line[i].color.R,line[i].color.G,line[i].color.B,255);
            SDL_RenderDrawLine(renderer,line[i].x1,line[i].x2,line[i].y1,line[i].y2);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
