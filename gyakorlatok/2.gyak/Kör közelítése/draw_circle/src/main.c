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

    int mouse_x,mouse_y;

    int color_palette[] = {20,20,600,60};
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
    int generate_button[] = {335,85,95,40};
    int scale_button[] = {210,85,95,40};
    int radius = 30;
    char text[10];
    int scale_arrow_right[] = {288,105,13}; 
    int scale_value[] = {243,85,27,40};
    int scale_arrow_left[] = {225,105,13};

    /**
     * Current circle color
    */
    int current_color[3] = {0,0,0}; //The default color is black

    /**
     * Define the circle array and the circle counter variable
    */
    int circles[MAX_CIRCLE_COUNT][6];
    int circle_count = 0;

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

    SDL_Surface* surface_generate = TTF_RenderText_Solid(font,"Generate",TextColor);
    SDL_Texture* texture_generate = SDL_CreateTextureFromSurface(renderer,surface_generate);  
    SDL_Rect textRect_generate = {335,85,95,40};

    sprintf(text,"%d",radius);
    SDL_Surface* surface_radius = TTF_RenderText_Solid(font,text,TextColor);
    SDL_Texture* texture_radius = SDL_CreateTextureFromSurface(renderer,surface_radius);  
    SDL_Rect textRect_radius;
    textRect_radius.x = scale_value[0]; 
    textRect_radius.y = scale_value[1];
    textRect_radius.w = scale_value[2];
    textRect_radius.h = scale_value[3];



    running = true;

    while(running){
        /**
         * Display the color palette
        */
        init_rectangle(&rectangle,color_palette);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderDrawRect(renderer,&rectangle);

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
         * Display the generate button
        */
        init_rectangle(&rectangle,generate_button);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderFillRect(renderer,&rectangle);

        /**
         * Display the scale button
        */
        init_rectangle(&rectangle,scale_button);
        SDL_RenderFillRect(renderer,&rectangle);
        draw_right_scale_arrow(renderer,scale_arrow_right);
        draw_left_scale_arrow(renderer,scale_arrow_left);

        /**
         * Display ttf text
        */
        SDL_RenderCopy(renderer, texture_generate, NULL, &textRect_generate);
        SDL_RenderCopy(renderer,texture_radius,NULL,&textRect_radius);

        /**
        * Draw circles
        */
        draw_circles(renderer,circles,circle_count);

        /**
         * Display changes
        */
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)){

            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    printf("%d %d\n",mouse_x,mouse_y);
                    if(mouse_x >= 20 && mouse_x <= 620 && mouse_y >= 130 && mouse_y <= 620){
                        save_circle(circles,&circle_count,mouse_x,mouse_y,radius,current_color);
                    }else if( mouse_x >= 20 && mouse_x <= 620 && mouse_y >= 20 && mouse_y <= 80){
                        for(int i = 0; i < 6; i++){
                            if(mouse_x >= colors[i][0] && mouse_x <= colors[i][0]+colors[i][2] && mouse_y >= colors[i][1] && mouse_y <= colors[i][1]+colors[i][3]){
                                current_color[0] = colors[i][4];
                                current_color[1] = colors[i][5];
                                current_color[2] = colors[i][6];
                                break;
                            }
                        }
                    }else if(mouse_x >= 335 && mouse_x <= 430 && mouse_y >= 85 && mouse_y <= 125){
                        mouse_x = 20 + (rand() % 600);
                        mouse_y = 130 + (rand() % 360);
                        save_circle(circles,&circle_count,mouse_x,mouse_y,30,current_color);
                    }else if(mouse_x >= 335 && mouse_x <= 430 && mouse_y >= 85 && mouse_y <= 125){

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
    TTF_Quit();
    SDL_FreeSurface(surface_generate);
    SDL_DestroyTexture(texture_generate);
    SDL_FreeSurface(surface_radius);
    SDL_DestroyTexture(texture_radius);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
