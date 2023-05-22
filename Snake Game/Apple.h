#pragma once
#include "Blocks.h"
#include <cstdlib> 
#include <ctime>
#include "SDL.h"

class Apple :public Blocks
{
public:

	Apple(int x=1, int y=1, int size=20):Blocks(x,y,size) {
		srand(time(0));
		POSITION_HORIZONTAL = rand() % 22 + 1;
		POSITION_VERTICAL = rand() % 18 + 1;
		BLOCK_COLOUR.red = 255; BLOCK_COLOUR.blue = 0; BLOCK_COLOUR.green = 0;
	}

	void operator=(const Apple a) {
		this->BLOCK_COLOUR = a.BLOCK_COLOUR;
		this->BLOCK_SIZE = a.BLOCK_SIZE;
		this->POSITION_HORIZONTAL = a.POSITION_HORIZONTAL;
		this->POSITION_VERTICAL = a.POSITION_VERTICAL;
	}
	
};

