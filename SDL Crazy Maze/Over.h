//=====================================================
//	File:		Over.h
//	Author:		Eliot Holland - Team Alpha
//	Course:		SGPG490
//	Assignment: Project 1
//	Title:		CRAZY MAZE
//	Description:
//		Game Over screen that apperas after every level
//======================================================
#pragma once
#ifndef _OVER_H_INCLUDED_
#define _OVER_H_INCLUDED_

#include "Engine.h"
#include "State.h"

/********************************
*								*
*		GAME OVER SCREEN		*
*								*
*********************************/
class Over : public State
{
private:
	SDL_Texture *overBack;			//Background
	SDL_Texture *menu_bt;			//Menu button images
	SDL_Texture *menu_bto;				
	SDL_Texture *exit_bt;			//Exit button images
	SDL_Texture *exit_bto;
	SDL_Texture *next_bt;			//Next level button images
	SDL_Texture *next_bto;

	Button menu;					//Menu button
	Button exit;					//Exit button
	Button next;					//Next level button
public:
	Over();							//Constructor
	~Over();						//Destructor
	void handle_event();
	void logic();
	void render();
};//end Over
/****************************************************************************
*	Name:	Over()
*
*	Description:	Constructor - Initiallizes all private variables
*
*****************************************************************************/
Over::Over()
{
	//background
	overBack =	loadTexture("end_back.bmp");
	//button images
	menu_bt =	loadTexture("menu.png");
	menu_bto =	loadTexture("menuo.png");
	exit_bt =	loadTexture("exit.png");
	exit_bto =	loadTexture("exito.png");
	//button objects
	menu.init(230, 600, 100, 50, menu_bt);
	exit.init(700, 600, 100, 50, exit_bt);
}//end Over()
/****************************************************************************
*	Name:	~Over()
*
*	Description:	Destructor - Deallocates memory
*
*****************************************************************************/
Over::~Over()
{
	SDL_DestroyTexture (overBack);
	SDL_DestroyTexture (menu_bt);
	SDL_DestroyTexture (menu_bto);
	SDL_DestroyTexture (exit_bt);
	SDL_DestroyTexture (exit_bto);

	overBack = NULL;
	menu_bt = NULL;
	menu_bto = NULL;
	exit_bt = NULL;
	exit_bto = NULL;
}//end ~Over()
/****************************************************************************
*	Name:	handle_event()
*
*	Description:	Handles events from keyboard/mouse
*
*	Arguments:		SDL_Event event
*
*	Modifies:		set_next_state()	- Changes the state
*					button.sprite		- used to change button image
*
*	Retruns:		None
*****************************************************************************/
void Over::handle_event()
{
	int x = 0, y = 0;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) set_next_state(STATE_EXIT);									

		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)											
			{
				set_next_state(STATE_MENU);
			}//end if
		}//end if
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;


				if ((x > menu.box.x)
					&& (x < menu.box.x + menu.box.w)
					&& (y > menu.box.y)
					&& (y < menu.box.y + menu.box.h))	menu.sprite = menu_bto;

				else if ((x > exit.box.x)
					&& (x < exit.box.x + exit.box.w)
					&& (y > exit.box.y)
					&& (y < exit.box.y + exit.box.h))	exit.sprite = exit_bto;

			}//end if
		}//end if
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;

				if ((x > menu.box.x)
					&& (x < menu.box.x + menu.box.w)
					&& (y > menu.box.y)
					&& (y < menu.box.y + menu.box.h))	set_next_state(STATE_MENU);

				else if ((x > exit.box.x)
					&& (x < exit.box.x + exit.box.w)
					&& (y > exit.box.y)
					&& (y < exit.box.y + exit.box.h))	set_next_state(STATE_EXIT);

				else
				{
					menu.sprite = menu_bt;
					exit.sprite = exit_bto;
				}//end else
			}//end if
		}//end if
	}//end while
}//end handle_event()
/****************************************************************************
*	Name:	logic()
*
*	Description:	Recovers the score and prints it to the screen
*
*	Arguments:		None
*
*	Modifies:		None
*
*	Retruns:		None
*****************************************************************************/
void Over::logic()
{

}
/****************************************************************************
*	Name:	render()
*
*	Description:	None
*
*	Arguments:		None
*
*	Modifies:		None
*
*	Retruns:		None
*****************************************************************************/
void Over::render()
{
	apply_surface(overBack, NULL);
	menu.show();
	exit.show();
}
#endif