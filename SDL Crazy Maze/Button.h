#pragma once
#ifndef _BUTTON_H_INCLUDED_
#define _BUTTON_H_INCLUDED_

#include "State.h"

class Button
{
public:	
	Button();
	~Button();
	void init(int x, int y, int w, int h,
		SDL_Texture* source);
	void show();

	SDL_Rect box;
	SDL_Texture *sprite;
};

Button::Button()
{

}
Button::~Button()
{

}
void Button::init(int x, int y, int w, int h,
	 SDL_Texture *source)
{
	//Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	//Set the sprite
	sprite = source;
}
void Button::show()
{
	apply_surface(sprite, &box);
}
#endif