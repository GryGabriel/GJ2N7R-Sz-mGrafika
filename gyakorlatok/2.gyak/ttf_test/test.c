#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    bool running;
    int error_code;
    int window_size = 640;

    /**
	 * SDL initialization
	 * */
	error_code = SDL_Init(SDL_INIT_EVERYTHING);
	if(error_code != 0){
		printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
		return error_code;
	}

    /**
	 * Create SDL window 
	 * */
	window = SDL_CreateWindow("Kör közelítése", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size, window_size, 0);

	/**
	 * Display SDL window
	 * */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if(renderer == NULL){
		printf("[ERROR Monitor cannot be created: %s\n", SDL_GetError());
		exit(1);
	} 

    /**
     * Initialize Text 
    */
    if(TTF_Init() != 0){
        printf("TTF_Init(): %s\n",TTF_GetError());
        exit(1);
    }
    TTF_Font* font = TTF_OpenFont("Arial.ttf", 40);
    SDL_Color TextColor = {0,0,255,0};
    SDL_Surface* surface = TTF_RenderText_Solid(font,"Hello",TextColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);  
    SDL_Rect textRect = {50,50,100,100};


    running = true;

    while(running){
        /**
         * Render ttf text
        */
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEBUTTONDOWN:
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
	 * Destroy SDL objects 
	 **/
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
