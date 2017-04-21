#pragma once
#include "constants.h"

class Control
{
public:
	Control();
	Control(SDL_Texture* font_input);
	~Control();
	SDL_Texture* font;
	SDL_Color white = { 225,255,255,255 };
	SDL_Color black = { 0,0,0,255 };
	SDL_Color red = { 225,0,0,255 };
	SDL_Color blue = { 0,255,0,255 };
	SDL_Color green = { 0,0,255,255 };
	char * numbers[30] = { "1","2","3","4","5","6","7","8","9","10",
		"11","12","13","14","15","16","17","18","19","20",
		"21","22","23","24","25","26","27","28","29","30"};
};