//=====================================================
//	File:		Main.cpp
//	Author:		Eliot Holland - Team Alpha
//	Course:		SGPG490
//	Assignment: Project 1
//	Title:		CRAZY MAZE
//	Description:
//		Get to the end of the maze before time runs out!
//======================================================
#include "ChangeState.h"

/****************************************************************************
*	Name:	main()
*
*	Description:	Main game loop
*
*	Inputs:			int argc
*					char* args[]
*
*	Outputs:		returns 0
*****************************************************************************/

int main( int argc, char* args[] )
{
	if (init() == false) return 1;

	stateID = STATE_MENU;					//Starts game at Main Menu
	currentState = new Menu();

	while (stateID != STATE_EXIT)
	{
		//SDL render functions
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(renderer);

		//core state cycle
		currentState->handle_event();
		currentState->logic();
		changeState();
		currentState->render();

		SDL_RenderPresent (renderer);		//Presents images on the screen
	}

	close();								//Deallocate memory and close
    return 0;
}