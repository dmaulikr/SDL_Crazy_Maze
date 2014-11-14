#pragma once
#ifndef _BRICK_H_
#define _BRICK_H_

#include "Square.h"

class Brick : public Square
{
private:
	SDL_Texture *brick;
public:
	Brick();
	~Brick();
	void init(int x, int y);
	void handle_event();
	void show();

	SDL_Rect brick_wall;
};

Brick::Brick()
{
	brick = loadTexture("Wall.png");
}

Brick::~Brick()
{
	SDL_DestroyTexture (brick);

	brick = NULL;
}

void Brick::init(int x, int y)
{
	brick_wall.x = x;
	brick_wall.y = y;
	brick_wall.w = 20;
	brick_wall.h = 20;
}

void Brick::handle_event()
{

}

void Brick::show()
{
	apply_surface(brick, &brick_wall);
}

#endif