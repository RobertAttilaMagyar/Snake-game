#pragma once
#include <vector>
#include "Blocks.h"
#include "SDL.h"
#include "Apple.h"
#include <ctime>
#include <iostream>

//I don't know why I named it tail.
class Tail
{
public:
	//The tail should have to have length, a vector full of blocks, because it's the simpliest way to increase the length
	int TAIL_LENGTH;
	std::vector<Blocks*> tailblocks;
	int VELOCITY_X, VELOCITY_Y; //Should have velocity
	bool dead; //That's necessary to terminate the game


	//Our pretty little constructor
	Tail(int length = 3)
	{
		TAIL_LENGTH = length;
		for (int i = 0; i < length; i++) {
			tailblocks.push_back(new Blocks());
			}
		VELOCITY_X = 1; VELOCITY_Y = 0;
		tailblocks.at(0)->POSITION_HORIZONTAL = 3;
		tailblocks.at(1)->POSITION_HORIZONTAL = 2;
		tailblocks.at(2)->POSITION_HORIZONTAL = 1;
		dead = false;
	}

	//A function to solve the problem of adding length to the snake
	void AddLength()
	{
		tailblocks.push_back(new Blocks()); 
		tailblocks.at(TAIL_LENGTH)->POSITION_HORIZONTAL = tailblocks.at(TAIL_LENGTH - 1)->POSITION_HORIZONTAL;
			tailblocks.at(TAIL_LENGTH)->POSITION_VERTICAL = tailblocks.at(TAIL_LENGTH - 1)->POSITION_VERTICAL;
		TAIL_LENGTH++; 
	}

	//A function to print the snake
	void PrintTail(SDL_Renderer* renderer) 
	{
		for (int i = 0; i < TAIL_LENGTH; ++i)
			tailblocks.at(i)->PrintBlock(renderer);
	}

	//A fuction to unprint the snake
	void UnprintTail(SDL_Renderer* renderer)
	{
		for (int i = 0; i < TAIL_LENGTH; ++i)
			tailblocks.at(i)->UnprintBlock(renderer);
	}

	//This function moves the snake, when the user doesn't hit any key
	void MoveSnake(SDL_Renderer* renderer)
	{
		dead = this->GAME_OVER();
		
		if (!dead) {
			this->UnprintTail(renderer);
			for (int i = (TAIL_LENGTH - 1); i > 0; --i)
				*tailblocks.at(i) = *tailblocks.at(i - 1);
			tailblocks.at(0)->POSITION_HORIZONTAL += VELOCITY_X;

			if (tailblocks.at(0)->POSITION_HORIZONTAL == 23)
				tailblocks.at(0)->POSITION_HORIZONTAL = 1;

			else if (tailblocks.at(0)->POSITION_HORIZONTAL == 0)
				tailblocks.at(0)->POSITION_HORIZONTAL = 22;

			tailblocks.at(0)->POSITION_VERTICAL -= VELOCITY_Y;

			if (tailblocks.at(0)->POSITION_VERTICAL == 19)
				tailblocks.at(0)->POSITION_VERTICAL = 1;

			else if (tailblocks.at(0)->POSITION_VERTICAL == 0)
				tailblocks.at(0)->POSITION_VERTICAL = 18;

			this->PrintTail(renderer);
		}
		}

	//We should be able to control the snake
	void ControlSnake(SDL_Event event, SDL_Renderer* renderer, bool run) {
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			if (VELOCITY_Y != -1) {
				VELOCITY_Y = 1;
				VELOCITY_X = 0;
			}
			break;

		case SDLK_DOWN:
			if (VELOCITY_Y != 1) {
				VELOCITY_Y = -1;
				VELOCITY_X = 0;
			}
			break;

		case SDLK_RIGHT:
			if (VELOCITY_X != -1) {
				VELOCITY_Y = 0;
				VELOCITY_X = 1;
			}
			break;

		case SDLK_LEFT:
			if (VELOCITY_X != 1) {
				VELOCITY_Y = 0;
				VELOCITY_X = -1;
			}
			break;

		case SDLK_SPACE:
			this->AddLength();
			break;

		default:
			break;
		}
		this->MoveSnake(renderer);

	}

	//This function "eats" the apple. It increases the length of the snake and creates a new apple somewhere in the gamefield
	Apple EatApple(Apple a, SDL_Renderer* renderer) {
		bool thing = true;
		bool thingy = false;
		srand(time(0));

		if (tailblocks.at(0)->IsEqual(a)) {

			this->AddLength();
			std::cout << "Score: " << this->TAIL_LENGTH << std::endl;
			a.POSITION_HORIZONTAL = rand() % 22 + 1;
			a.POSITION_VERTICAL = rand() % 18 + 1;
			while (thing) {
				for (int i = 0; i < TAIL_LENGTH; ++i) {
					if (tailblocks.at(i)->IsEqual(a)) {
						thingy = true;
						a.POSITION_HORIZONTAL = rand() % 22 + 1;
						a.POSITION_VERTICAL = rand() % 18 + 1;
						//i = 0;
					}

				}
				if (thingy) {
					thing = true;
					thingy = false;
				}
				else thing = false;
			}
		}

		return a;
	}

	//This function detects, if the snake bites it's tail and terminates the game
	bool GAME_OVER() {
		bool thing = false;
		for (int i = 1; i < TAIL_LENGTH; ++i) {
			if(!thing) thing = tailblocks.at(0)->IsEqual(*tailblocks.at(i));
			}
		return thing;
	}
};

