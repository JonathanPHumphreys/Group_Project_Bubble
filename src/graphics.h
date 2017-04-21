// GRAPHICS.H

#pragma once
#include "constants.h"

class Balloon
{
private:
	char* path;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
public:
	plot dimensions;
	SDL_Rect collider;
	plot position;
	plot velocity;

	// functions
	Balloon();
	Balloon(SDL_Renderer*, char*, float, float, float, float);
	void update();
	void render();
};