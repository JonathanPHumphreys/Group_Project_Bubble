// GRAPHICS.CPP

#include "graphics.h"


Balloon::Balloon() {}

Balloon::Balloon(SDL_Renderer* game_renderer, char* file_path, float x, float y, float w, float h)
{
	srand(time(NULL));
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

	ballonValue = rand() % 30;


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

void Balloon::render(vector <Control> cv) 
{
	dst.x = position.x; 								// sets dst x position
	dst.y = position.y; 								// sets dst y position
	dst.w = dimensions.x; 								// sets dst width
	dst.h = dimensions.y; 								// sets dst height

	fontdst.x = position.x + 10;
	fontdst.y = position.y + 15;
	fontdst.w = (dimensions.x / 1.25);
	fontdst.h = (dimensions.y / 1.25);
	//positond fonts here too 


	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_RenderCopy(renderer, cv[ballonValue].font  , NULL, &fontdst);

}
