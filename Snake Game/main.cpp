//This is my first attempt to create a Snake game in C++
#include <iostream>
#include "SDL.h"
#include "Blocks.h"
#include "Tail.h"
#include "Apple.h"


Uint32 timer(Uint32 ms, void* param) {
	SDL_Event ev;
	ev.type = SDL_USEREVENT;
	SDL_PushEvent(&ev);
	return ms;
}



int main(int argc, char *argv[]) 
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("SDL can't be used %s", SDL_GetError());
		exit(1);
	}

	//Creating the window
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 440, 360, 0);
	if (window == NULL) {
		SDL_Log("Window can't be created %s", SDL_GetError());
		exit(1);
	}

	//Creating the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL) {
		SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
		exit(1);
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);



	//Here starts the important thingy
	
	Tail snake;
	snake.PrintTail(renderer);
	SDL_RenderPresent(renderer);
	SDL_TimerID id = SDL_AddTimer(130, timer, NULL);

	
	bool run = true;
	Apple a;
	a.PrintBlock(renderer);
	

	//Creating te gameloop
	while (run) {
		snake.PrintTail(renderer);
		SDL_Event event;
		SDL_WaitEvent(&event);
		a.PrintBlock(renderer);
		
		switch (event.type)
		{
		case(SDL_KEYDOWN):
			snake.ControlSnake(event, renderer, run);
			a = snake.EatApple(a, renderer);
			if (event.key.keysym.sym == SDLK_ESCAPE) run = false;
			break;
			break;

		case SDL_USEREVENT:
			snake.MoveSnake(renderer);
			a = snake.EatApple(a, renderer);
			break;
		}
		SDL_RenderPresent(renderer); 
	}
	
	SDL_Quit();
	return EXIT_SUCCESS;
}
