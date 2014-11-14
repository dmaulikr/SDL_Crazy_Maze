#pragma once
#ifndef _Bomb_H_
#define _Bomb_H_

#include "Square.h"

class Bomb : Square
{
private:
	SDL_Texture *bmb;
public:
	Bomb();
	~Bomb();
	void init(int x, int y);
	void handle_event();
	void show();

	SDL_Rect Bomb_box;			//used to evaluate position
};


Bomb::Bomb()
{
	bmb = loadTexture("bomb4.png");
}

Bomb::~Bomb()
{
	SDL_DestroyTexture (bmb);

	bmb = NULL;
}

void Bomb::init(int x, int y)
{
	Bomb_box.x = x;
	Bomb_box.y = y;
	Bomb_box.w = 20;
	Bomb_box.h = 20;
}

void Bomb::handle_event()
{

}

void Bomb::show()
{
	apply_surface(bmb, &Bomb_box);
}
#endif