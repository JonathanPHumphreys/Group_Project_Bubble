// ENTITIES.H

#pragma once
#include "constants.h"
#include "Control.h"

class Panel
{
private:
	char* path;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect dst;
	SDL_Rect fontdst;
public:
	plot dimensions;
	plot position;
	plot velocity;

	// functions
	Panel();
	Panel(SDL_Renderer*, char*, float, float, float, float);
	//void update();
	void render();
	void render(vector <Control> cv, int num);
};