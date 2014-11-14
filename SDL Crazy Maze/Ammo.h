#pragma once
#ifndef _Ammo_H_
#define _Ammo_H_

#include "Square.h"

class Ammo : Square
{
private:
	SDL_Texture *amo;
public:
	Ammo();
	~Ammo();
	void init(int x, int y);
	void handle_event();
	void show();

	SDL_Rect Ammo_box;			//used to evaluate position
};


Ammo::Ammo()
{
	amo = loadTexture("phasegun_bullet_small.png");
}

Ammo::~Ammo()
{
	SDL_DestroyTexture (amo);

	amo = NULL;
}

void Ammo::init(int x, int y)
{
	Ammo_box.x = x;
	Ammo_box.y = y;
	Ammo_box.w = 20;
	Ammo_box.h = 20;
}

void Ammo::handle_event()
{

}

void Ammo::show()
{
	apply_surface(amo, &Ammo_box);
}
#endif