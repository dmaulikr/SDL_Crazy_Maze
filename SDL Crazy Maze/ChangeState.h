#pragma once
#ifndef _CHANGESTATE_H_INCLUDED
#define _CHANGESTATE_H_INCLUDED

#include "Menu.h"
#include "Help.h"
#include "Over.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"

//State object
State *currentState = NULL;

void close()
{
	delete currentState;
	SDL_DestroyRenderer (renderer);
	renderer = NULL;
	SDL_DestroyWindow( window );
	window = NULL;
	IMG_Quit();
	SDL_Quit();
}
void changeState()
{
	if (nextState != STATE_NULL)
	{
		if (nextState != STATE_EXIT)
		{
			delete currentState;
		}

		switch (nextState)
		{
		case STATE_MENU:
			currentState = new Menu();		//Instantiate the state
			break;
		case STATE_HELP:
			currentState = new Help();
			break;
		
		case STATE_LVL1:
			currentState = new Level_1();
			break;

		//UPDATED : 11/9/14 - Eliot Holland****************************
		case STATE_LVL2:
			currentState = new Level_2();
			break;

		case STATE_LVL3:
			currentState = new Level_3();
			break;
		//************************************************************
		
		//UPDATED : 11/3/14 - Eliot Holland**************************
		case STATE_OVER:
			currentState = new Over();		//Game Over state
			break;
		//************************************************************
		}

		stateID = nextState;
		nextState = STATE_NULL;
	}
}

#endif