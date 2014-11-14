//=====================================================
//	File:		Engine.h
//	Author:		Eliot Holland - Team Alpha
//	Course:		SGPG490
//	Assignment: Project 1
//	Title:		CRAZY MAZE
//	Description:
//		Global variables and functions are declared here
//======================================================
//Precompiler code
#pragma once
#ifndef _ENGINE_H_INCLUDED_
#define _ENGINE_H_INCLUDED_

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<sstream>

const int SCREEN_WIDTH =	1024;
const int SCREEN_HEIGHT =	768;
const int SCREEN_BPP =		32;				//bytes per pixle

//Get key state
const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

TTF_Font *font;
SDL_Color textColor = { 255, 255, 255 };

SDL_Window*		window;						//window that's rendered to
SDL_Renderer*	renderer;					//window renderer

SDL_Event event;							//event object
	
enum GAME_STATE	{	STATE_NULL,				//used to maintain state
					STATE_MENU,				//Main Menu
					STATE_LVL1,				//Level 1
					STATE_LVL2,				//Level 2
					STATE_LVL3,				//Level 3
					STATE_OVER,				//Game Over
					STATE_HELP,				//Help Menu
					STATE_EXIT	};			//Quit

int stateID;							//state to maintain
int nextState;							//used to change states smoothly

struct time
{
	int seconds;
	int minutes;
};//end time

struct final_score_time
{
	int total_score;
	int lvl1_score;
	int lvl2_score;
	int lvl3_score;

	time lvl1_time;
	time lvl2_time;
	time lvl3_time;
};//end final_score_time

final_score_time final;		//final score keeper

//======================================================
//Name:			init()
//Description:	Initializes all SDL components and 
//				extensions
//Arguments:	None
//Modifies:		None
//Returns:		True - if successful
//======================================================
bool init()							
{
	//Initialize SDL, return false if failed
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) return false;
    
	//Create window
	window = SDL_CreateWindow( "Crazy Maze", 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, 
								SCREEN_HEIGHT, 
								SDL_WINDOW_SHOWN );

	//Check window
    if( window == NULL ) return false;
		
	//set renderer
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	//check renderer
    if( renderer == NULL ) return false;
        
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) return false;

	//Initialize TTF (TrueText Font)
	if( (TTF_Init() == -1 ) ) return false;
	font = TTF_OpenFont("stocky.ttf", 28);

	//Initialize SDL_Mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		return false;
	}



	return true;
}
/****************************************************************************
*	Name:	loadTexture()
*
*	Description:	Searches for and loads an image into the instance
*
*	Arguments:		std::string
*
*	Modifies:		None
*
*	Retruns:		newTexture -  The loaded image
*****************************************************************************/
SDL_Texture *loadTexture (std::string filename)
{
    SDL_Texture* newTexture = NULL;									//The final texture

    SDL_Surface* loadedSurface = IMG_Load( filename.c_str() );		//Load image at specified path
    if( loadedSurface == NULL )										//error check
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 117, 0 ) );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", filename.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
void apply_surface(	SDL_Texture* source,
					SDL_Rect* dest)
{
	if (dest != NULL)
	{
		SDL_Rect renderQuad = {	dest->x,
								dest->y,
								dest->w,
								dest->h};
		SDL_RenderCopy(renderer, source, NULL, &renderQuad);
	}
	else
	{
		SDL_RenderCopy(renderer, source, NULL, NULL);
	}
}
void set_next_state(int newState)
{
	if (nextState != STATE_EXIT)
	{
		nextState = newState;
	}
}

bool check_collision(SDL_Rect a, SDL_Rect b)
{
	//coordinates of each box's sides
	int leftA,		leftB;
	int rightA,		rightB;
	int topA,		topB;
	int bottomA,	bottomB;

	//rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	return true;
}

#endif