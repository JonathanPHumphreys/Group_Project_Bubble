// ENTITIES.H

#pragma once
#include "constants.h"

class Panel
{
private:
	char* path;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
public:
	plot dimensions;
	plot position;
	plot velocity;

	// functions
	Panel();
	Panel(SDL_Renderer*, char*, float, float, float, float);
	//void update();
	void render();
};