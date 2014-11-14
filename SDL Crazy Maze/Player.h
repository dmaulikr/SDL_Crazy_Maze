#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Square.h"

class Player : public Square
{
private:
	SDL_Texture *plr;
	//UPDATED - 11/9/14 - Eliot Holland*****************************************
	int loc_x;		//X start location
	int loc_y;		//Y start location
	//**************************************************************************
public:
	Player();
	~Player();
	void init(int x, int y);
	void handle_event();
	void show();
	//UPDATED - 11/9/14 - Eliot Holland*****************************************
	void reset();   //reset the player
	//**************************************************************************

	SDL_Rect player_box;	//used to evaluate position
};


Player::Player()
{
	plr = loadTexture("Player.png");
}

Player::~Player()
{
	SDL_DestroyTexture (plr);

	plr = NULL;
}

void Player::init(int x, int y)
{
	//UPDATED - 11/9/14 - Eliot Holland*****************************************
	loc_x = x;		//set start location
	loc_y = y;
	//*************************************************************************

	player_box.x = x;
	player_box.y = y;
	player_box.w = 18;
	player_box.h = 18;
}

void Player::handle_event()
{

}

void Player::show()
{
	apply_surface(plr, &player_box);
}
//UPDATED - 11/9/14 - Eliot Holland*****************************************
void Player::reset()
{
	//reset player to start location
	player_box.x = loc_x;
	player_box.y = loc_y;
}
//*************************************************************************
#endif