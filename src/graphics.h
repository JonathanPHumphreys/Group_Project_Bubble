// GRAPHICS.H

#pragma once
#include "constants.h"
#include "Control.h"

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
	SDL_Rect dst;
	SDL_Rect fontdst;

	int ballonValue = 0;

	// functions
	Balloon();
	Balloon(SDL_Renderer*, char*, float, float, float, float);
	void update();
	void render(vector <Control> cv) ;
};