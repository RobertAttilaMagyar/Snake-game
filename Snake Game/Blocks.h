#pragma once
#include "SDL.h"
#include "Colour.h"

class Blocks
{
public:
	//Our blocks have to have X and Y coordinates, size and a colour. (different objects have different colours).
	int POSITION_HORIZONTAL, POSITION_VERTICAL, BLOCK_SIZE;
	Colour BLOCK_COLOUR;

	//Constructor
	Blocks( int x = 1, int y = 1,int size = 20 )
	{
		POSITION_HORIZONTAL = x;
		POSITION_VERTICAL = y;
		BLOCK_SIZE = size;
		BLOCK_COLOUR.red = 114; BLOCK_COLOUR.blue = 206; BLOCK_COLOUR.green = 227;
	}

	//A function to change the colour of different blocks
	void SetBlockColour(int r=114, int g=206, int b=227) {
		BLOCK_COLOUR.red = r; BLOCK_COLOUR.blue = b; BLOCK_COLOUR.green = g;
	}

	//A function to print the blocks
	void PrintBlock(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, BLOCK_COLOUR.red, BLOCK_COLOUR.green, BLOCK_COLOUR.blue, 255);
		for (auto i = (POSITION_HORIZONTAL - 1) * 20; i <= (POSITION_HORIZONTAL) * 20; ++i) {
			for (auto j = (POSITION_VERTICAL - 1) * 20; j <= (POSITION_VERTICAL) * 20; ++j) {
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	//We should be able to unprint blocks too
	void UnprintBlock(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		for (auto i = (POSITION_HORIZONTAL - 1) * 20; i <= (POSITION_HORIZONTAL) * 20; ++i) {
			for (auto j = (POSITION_VERTICAL - 1) * 20; j <= (POSITION_VERTICAL) * 20; ++j) {
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	//Overloading the equation operator
	void operator= (const Blocks b) {
		POSITION_HORIZONTAL = b.POSITION_HORIZONTAL;
		POSITION_VERTICAL = b.POSITION_VERTICAL;
		BLOCK_SIZE = b.BLOCK_SIZE;
		BLOCK_COLOUR = b.BLOCK_COLOUR;
	}

	//This function is necessary to terminate the game and make the snake able to eat the apple
	bool IsEqual(Blocks b) {
		return ((this->POSITION_HORIZONTAL == b.POSITION_HORIZONTAL) && (this->POSITION_VERTICAL == b.POSITION_VERTICAL));
	}
};

