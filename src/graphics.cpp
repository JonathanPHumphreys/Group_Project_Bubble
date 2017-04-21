// GRAPHICS.CPP

#include "graphics.h"

Balloon::Balloon() {}

Balloon::Balloon(SDL_Renderer* game_renderer, char* file_path, float x, float y, float w, float h)
{
	renderer = game_renderer;
	path = file_path;
	texture = IMG_LoadTexture(renderer, path);
	position = { x, y };
	dimensions = { w, h };
	velocity = { 0, 0 };

	collider.x = position.x;
	collider.y = position.y;
	collider.w = dimensions.x;
	collider.h = dimensions.y;
}

void Balloon::update()
{
	if (velocity.x)
	{
		position.x += velocity.x;
		collider.x += velocity.x;
	}

	if (velocity.y)
	{
		position.y += velocity.y;
		collider.y += velocity.y;
	}
}

void Balloon::render() 
{
	SDL_Rect dst;
	dst.x = position.x; 								// sets dst x position
	dst.y = position.y; 								// sets dst y position
	dst.w = dimensions.x; 								// sets dst width
	dst.h = dimensions.y; 								// sets dst height

	SDL_RenderCopyEx(renderer, texture, NULL, &dst, NULL, NULL, SDL_FLIP_NONE);
}