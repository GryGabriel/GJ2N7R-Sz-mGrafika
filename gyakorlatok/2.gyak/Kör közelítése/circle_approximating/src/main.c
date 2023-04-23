#include "circle.h"

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>



int main(int argc, char* argv[])
{
	Circle circle;
	double area;
	
	set_circle_data(&circle, 300, 300, 150);
	area = calc_circle_area(&circle);
	
	printf("Circle area: %lf\n", area);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	bool running;

	int error_code;
	int window_size=640;


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


	running = true;

	while(running){
		/**
		 * Change backround color to white
		 * */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    SDL_RenderClear(renderer);

	    /**
	     * Change draw color to black and draw a circle
	     * */
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	    //approx_circle(renderer, circle.x,circle.y,circle.radius);
	    //approx_circle_given_steps(renderer, circle.x,circle.y,circle.radius, 3.0);
	    approx_circle_given_angle(renderer, circle.x,circle.y,circle.radius, 5.0);
	    //approx_circle_given_length(renderer, circle.x,circle.y,circle.radius,10.0);

	    /**
	     * Display changes
	     * */
	    SDL_RenderPresent(renderer);

	    int mousex,mousey;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mousex,&mousey);
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
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}