//=====================================================
//	File:		Timer.h
//	Author:		David Goodwin - Team Alpha
//	Course:		SGPG490
//	Assignment: Project 1
//	Title:		CRAZY MAZE
//	Description:
//		Artificial Intelligence and Game Object for
//		enemies.
//======================================================
#pragma once
#ifndef _AI_H_
#define _AI_H_

#include "Engine.h"
//====================================================
//Class : AI
//====================================================
class AI
{
private:
	SDL_Texture *artint;    
	int ai_xVel;
	int ai_yVel;
	int counter;
	//MOD : 11/4/14 - Eliot Holland****************************
	int loc_x;	// X location
	int loc_y;  // Y location
	//*********************************************************
public:
	AI();
	~AI();
	SDL_Rect ai_box;
	void init(int x, int y, int xVel, int yVel);
	void handle_event(SDL_Rect boundaries, Brick wall[], int px, int py); // (David Goodwin 11/2/14)
	void show();
	//MOD : 11/4/14 - Eliot Holland**************************
	void reset();   //function to reset position
	//*******************************************************
	bool AICollision(SDL_Rect boundaries, Brick wall[]); // (David Goodwin 11/2/14)
};//end AI

AI::AI()
{
	artint = loadTexture("AIblob.png");
}

AI::~AI()
{
	SDL_DestroyTexture (artint);
	artint = NULL;
}


void AI::init(int x, int y, int xVel, int yVel)
{
	//MOD : 11/4/14 - Eliot Holland**************************
	//set reset location
	loc_x = x;
	loc_y = y;
	//*******************************************************
	ai_box.x = x;
	ai_box.y = y;
	ai_box.w = 20;
	ai_box.h = 20;
	ai_xVel = 0;  //xVel;
	ai_yVel = 0;  //yVel;
	counter = 0;
}

void AI::handle_event(SDL_Rect boundaries, Brick wall[], int px, int py) // (David Goodwin 11/2/14)
{
	// AI controller
	int Rnum; // random number
	bool hit;

	if (counter > 900) // Changes AI speed  (on my system the ai runs slower at 900 to 1k.  The lower the number the faster it moves)
	{
		counter = 0;
		hit = true;
	}
	else
	{
		counter ++;
		hit = false;
	}


	while(hit)
	{
		hit = false;		
		
		// Make it random
		Rnum = (rand() % 10) + 1;  // original Rnum = (rand() % 10) + 1;
		
		// select direction
		switch (Rnum)
		{
		case 1:
			// Go North
			ai_box.y -= 20;
			if (AICollision(boundaries, wall))
			{
				ai_box.y += 20;
				hit = true;
			}
			break;
		case 2:
			// Go East
			ai_box.x -= 20;
			if (AICollision(boundaries, wall))
			{
				ai_box.x += 20;
				hit = true;
			}
			break;
		case 3:
			// Go South
			ai_box.y += 20;
			if (AICollision(boundaries, wall))
			{
				ai_box.y -= 20;
				hit = true;
			}
			break;
		case 4:
			// Go West
			ai_box.x += 20;
			if (AICollision(boundaries, wall))
			{
				ai_box.x -= 20;
				hit = true;
			}
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			// Persue Player
			if(px > ai_box.x)
			{
				ai_box.x += 20;  // Go West
				if (AICollision(boundaries, wall))
				{
					ai_box.x -= 20;  // Go East
					hit = true;
				}
			}
			else if(px < ai_box.x)
			{
				ai_box.x -= 20;  // Go East
				if (AICollision(boundaries, wall))
				{
					ai_box.x += 20;  // Go West
					hit = true;
				}
			}
			else if(py > ai_box.y)
			{
				ai_box.y += 20;  // Go South
				if (AICollision(boundaries, wall))
				{
					ai_box.y -= 20;  // Go North
					hit = true;
				}
			}
			else if(py < ai_box.y) 
			{
				ai_box.y -= 20;  // Go North
				if (AICollision(boundaries, wall))
				{
					ai_box.y += 20;  // Go South
					hit = true;
				}
			}
			break;
		}//end while
	}
}

void AI::show()
{
	apply_surface(artint, &ai_box);
}

bool AI::AICollision(SDL_Rect boundaries, Brick wall[])
{
	//AI Boundries / collision checking - (David Goodwin 10/23/14)	
	if ((ai_box.x < boundaries.x) || (ai_box.x + ai_box.w > boundaries.w) || (ai_box.y < boundaries.y) || (ai_box.y + ai_box.h > boundaries.h))
	{
		return true;
	}

	for (int i = 0; i <164; ++i)
	{
		switch ( check_collision(ai_box, wall[i].brick_wall))
		{
		case true: return true; break;
		case false: break;
		}
	}

	return false;
}

//MOD : 11/4/14 - Eliot Holland**************************
void AI::reset()
{
	ai_box.x = loc_x;
	ai_box.y = loc_y;
}
//*******************************************************
#endif