#include "draw_circle.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_CIRCLE_COUNT 300

int main(){
    srand(time(NULL));

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_Rect rectangle;

    bool running;
    int error_code;
    int window_size = 640;
    int radius = 50;

    int mouse_x,mouse_y;

    //int color_palette[] = {20,20,600,60};
    int colors[][7] = 
    {
        {50,30,65,40, 255,255,255},
        {145,30,65,40, 255,255,0},
        {240,30,65,40, 0,255,0},
        {335,30,65,40, 0,0,255},
        {430,30,65,40, 255,0,0},
        {525,30,65,40, 0,0,0}
    };

    int drawing_palette[] = {20,130,600,490};

    int draw_button[] = {145,85,65,40}; 
    int generate_button[] = {273,85,95,40};
    int move_button[] = {430,85,65,40};

    bool draw_mode = true; //if false, move mode is ON


    /**
     * Current circle color
    */
    int current_color[3] = {0,0,0}; //The default color is black

    /**
     * Define the circle array and the circle counter variable
    */
    int circles[MAX_CIRCLE_COUNT][6];
    int circle_counter = 0;

    /**
	 * SDL initialization
	 */
	error_code = SDL_Init(SDL_INIT_EVERYTHING);
	if(error_code != 0){
		printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
		return error_code;
	}

    /**
	 * Create SDL window 
	 */
	window = SDL_CreateWindow("Kör közelítése", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size, window_size, 0);

	/**
	 * Display SDL window
	 */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if(renderer == NULL){
		printf("[ERROR Monitor cannot be created: %s\n", SDL_GetError());
		exit(1);
	} 
    
    /**
    * Set white background color
    */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    /**
     * Initialize Text 
    */
    if(TTF_Init() == -1){
        printf("TTF_Init(): %s\n\n",TTF_GetError());
        exit(1);
    }
    TTF_Font* font = TTF_OpenFont("OpenSans-Light.ttf", 15);
    SDL_Color TextColor = {255,255,255,255};

    SDL_Surface* surface_draw = TTF_RenderText_Solid(font,"Draw",TextColor);
    SDL_Texture* texture_draw = SDL_CreateTextureFromSurface(renderer,surface_draw);  
    SDL_Rect textRect_draw = {145,85,65,40};

    SDL_Surface* surface_generate = TTF_RenderText_Solid(font,"Generate",TextColor);
    SDL_Texture* texture_generate = SDL_CreateTextureFromSurface(renderer,surface_generate);  
    SDL_Rect textRect_generate = {273,85,95,40};

    SDL_Surface* surface_move = TTF_RenderText_Solid(font,"Move",TextColor);
    SDL_Texture* texture_move = SDL_CreateTextureFromSurface(renderer,surface_move);  
    SDL_Rect textRect_move = {430,85,65,40};



    running = true;

    while(running){
        /**
         * Display the color palette
        */
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        init_rectangle(&rectangle,drawing_palette);
        SDL_RenderDrawRect(renderer,&rectangle);

        for(int i=0;i<sizeof(colors)/sizeof(int)/7;i++){
            SDL_SetRenderDrawColor(renderer,colors[i][4],colors[i][5],colors[i][6],0);
            init_rectangle(&rectangle,colors[i]);
            SDL_RenderFillRect(renderer,&rectangle);
            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderDrawRect(renderer,&rectangle);
        }

        /**
         * Display the draw button
        */
        init_rectangle(&rectangle,draw_button);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderFillRect(renderer,&rectangle);

        /**
         * Display the move button
        */
        init_rectangle(&rectangle,move_button);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderFillRect(renderer,&rectangle);

        

        /**
         * Display the generate button
        */
        init_rectangle(&rectangle,generate_button);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderFillRect(renderer,&rectangle);

        /**
         * Display ttf text
        */
        SDL_RenderCopy(renderer, texture_draw, NULL, &textRect_draw);
        SDL_RenderCopy(renderer, texture_generate, NULL, &textRect_generate);
        SDL_RenderCopy(renderer, texture_move, NULL, &textRect_move);

        /**
        * Draw circles
        */
        draw_circles(renderer,circles,circle_counter);

        /**
         * Display changes
        */
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)){

            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    /**
                     * Get mouse state
                    */
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    printf("%d %d\n",mouse_x,mouse_y);

                    /**
                     * If the user chooses draw mode
                    */
                    if(check_coordinates(mouse_x,mouse_y,145,210,85,125)){
                        draw_mode = true;
                    /**
                     * If the user chooses move mode
                    */
                    }else if(check_coordinates(mouse_x,mouse_y,430,495,85,125)){
                        draw_mode = false;
                    
                    /**
                     * If the user clicks on the generate button
                    */
                    }else if(check_coordinates(mouse_x,mouse_y,273,368,85,125) && draw_mode){
                        mouse_x = 20 + (rand() % 600);
                        mouse_y = 130 + (rand() % 360);
                        save_circle(circles,&circle_counter,mouse_x,mouse_y,radius,current_color);

                    /**
                     * If the user clicks inside the drawing palette
                    */
                    }else if(check_coordinates(mouse_x,mouse_y,20,620,130,620)){
                        //If draw mode is enabled
                        if(draw_mode){
                            save_circle(circles,&circle_counter,mouse_x,mouse_y,radius,current_color);
                        
                        //Else if move mode is enabled
                        }else{
                            move_circle(renderer,circles,circle_counter,mouse_x,mouse_y);
                        }

                    /**
                     * If the user clicks inside the color palette
                    */
                    }else if(check_coordinates(mouse_x,mouse_y,20,620,20,80)){
                        for(int i = 0; i < 6; i++){
                            if(mouse_x >= colors[i][0] && mouse_x <= colors[i][0]+colors[i][2] && mouse_y >= colors[i][1] && mouse_y <= colors[i][1]+colors[i][3]){
                                current_color[0] = colors[i][4];
                                current_color[1] = colors[i][5];
                                current_color[2] = colors[i][6];
                                break;
                            }
                        }
                    }

                    break;
                case SDL_KEYDOWN:
                case SDL_SCANCODE_Q:
                    running = false;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
            }

        }
    }

    /**
	 * Destroy SDL,TTF objects 
	 **/
    TTF_CloseFont(font);
    SDL_FreeSurface(surface_draw);
    SDL_DestroyTexture(texture_draw);
    SDL_FreeSurface(surface_generate);
    SDL_DestroyTexture(texture_generate);
    SDL_FreeSurface(surface_move);
    SDL_DestroyTexture(texture_move);
    TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
