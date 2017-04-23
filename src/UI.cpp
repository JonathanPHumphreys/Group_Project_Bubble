// UI.CPP

#include "UI.h"

Panel::Panel() {}

Panel::Panel(SDL_Renderer* game_renderer, char* file_path, float x, float y, float w, float h)
{
	renderer = game_renderer;
	path = file_path;
	texture = IMG_LoadTexture(renderer, path);
	position = { x, y };
	dimensions = { w, h };
	velocity = { 0, 0 };
}

void Panel::render()
{
	
	dst.x = position.x; 								// sets dst x position
	dst.y = position.y; 								// sets dst y position
	dst.w = dimensions.x; 								// sets dst width
	dst.h = dimensions.y; 								// sets dst height

	SDL_RenderCopyEx(renderer, texture, NULL, &dst, NULL, NULL, SDL_FLIP_NONE);
}

void Panel::render(vector <Control> cv, int num)
{

	dst.x = position.x; 								// sets dst x position
	dst.y = position.y; 								// sets dst y position
	dst.w = dimensions.x; 								// sets dst width
	dst.h = dimensions.y; 								// sets dst height

	SDL_RenderCopyEx(renderer, texture, NULL, &dst, NULL, NULL, SDL_FLIP_NONE);
}