//=====================================================
//	File:		Timer.h
//	Author:		Eliot Holland - Team Alpha
//	Course:		SGPG490
//	Assignment: Project 1
//	Title:		CRAZY MAZE
//	Description:
//		Calculates the time into Minutes and Seconds
//		Also sets the timer for each level and
//		contains all scoring objects
//======================================================
#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Engine.h"

//====================================================
//Class : Timer
//====================================================

class Timer : public Square
{
private:
	int prevTime;       //used to calculate time
	int startTicks;		//
	int ticks;			//
	Mix_Chunk *warning;			//time limit warning
	SDL_Texture *play_clock;	//Texture for font render
	SDL_Rect time_box;			//Render location
	SDL_Texture *finish;		//finish line image
public:
	Timer();
	~Timer();
	SDL_Rect finish_box;		//Render location
	void init(int x, int y);	//initialize finish line
	void handle_event();
	void show();		//render
	void calculate();	//time in seconds and minutes
	int seconds;		//calculated seconds
	int minutes;		//calculated minutes
	int temp_score;		//per level score
};//end Timer
//======================================================
//Name:			Timer()
//Description:	Initializes local variables and objects
//				General Constructor
//Arguments:	None
//Modifies:		None
//Returns:		None
//======================================================
Timer::Timer()
{ 
	minutes = 0;
	seconds = 0;
	startTicks = 0;					
	ticks = 0;
	prevTime = SDL_GetTicks();		//initialize to current tick count
	warning = Mix_LoadWAV("Warning.wav");
	play_clock = NULL;				//just initialize variable
	finish = loadTexture("finish.png");

	time_box.x = 440;				//set screen location
	time_box.y = 130;
	time_box.w = 150;
	time_box.h = 30;
}//end Timer()
//======================================================
//Name:			~Timer()
//Description:	Deallocates memory
//				General Destructor
//Arguments:	None
//Modifies:		None
//Returns:		None
//======================================================
Timer::~Timer()
{
	SDL_DestroyTexture(play_clock);
	play_clock = NULL;
	SDL_DestroyTexture( finish );
	finish = NULL;
	Mix_FreeChunk(warning);
}//end ~Timer();

void Timer::init( int x, int y )
{
	//finish line
	finish_box.x = x;		//coordinates for rendering
	finish_box.y = y;
	finish_box.w = 20;
	finish_box.h = 20;
}//end init()

void Timer::handle_event()
{
	if( nextState == STATE_LVL2 )	//if next level
	{								//put info in score object
		final.lvl1_score = temp_score;	
		final.lvl1_time.minutes = minutes;
		final.lvl1_time.seconds = seconds;
	}//end if
}//end handle_event()
void Timer::calculate()
{
	ticks = SDL_GetTicks() - prevTime;			//reset count
	ticks = ticks / 1000;						//convert to seconds

	if (seconds == 60)
	{
		startTicks = ticks;						//set to current tick count
		seconds = 0;
		minutes += 1;
	}

	if (seconds < 60) seconds = ticks - startTicks;

	if ((seconds == 60) && (minutes != 2))
	{
		if (Mix_PlayChannel(-1, warning, 0) == -1)
		{
			set_next_state(STATE_EXIT);
		}
	}
}

void Timer::show()
{
	//Set Time render surface
	std::stringstream clock;

	if (seconds < 10)	clock << 
						"Time: " <<
						minutes << 
						":0" << 
						seconds;

	else if ((seconds == 0) || (seconds == 60))	clock << 
												"Time: " << 
												minutes << 
												":00";

	else clock << "Time: " << minutes << ":" << seconds;

	play_clock = SDL_CreateTextureFromSurface( 
					renderer, 
					TTF_RenderText_Solid(
					font,
					clock.str().c_str(),
					textColor) );

	apply_surface( play_clock, &time_box );
	apply_surface( finish, &finish_box );
}

#endif