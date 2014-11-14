//=====================================================
//	File:		Level_1.h
//	Author:		Eliot Holland - Team Alpha
//	Course:		SGPG490
//	Assignment: Project 1
//	Title:		CRAZY MAZE
//	Description:
//		Level 1 state. Includes all game elements
//		and logic necessary for Level 1.
//======================================================
#pragma once
#ifndef _LEVEL_1_H_INCLUDED_
#define _LEVEL_1_H_INCLUDED_

#include "State.h"
#include "Square.h"
#include "Brick.h"
#include "Player.h"
#include "Timer.h"
#include "Bomb.h"
#include "Ammo.h"
#include "AI.h"


class Level_1 : public State
{
private:
	SDL_Texture *gameBack;
	SDL_Rect boundaries;
	SDL_Rect plyr_rect;
	
	Brick brick[164];		//Maze object
	Player player;			//Player object

	Timer timer;			//Timer object

	//MOD : 11/4/14 - Eliot Holland - Original - David Goodwin******
	AI enemy[3];			//array of enemy objects
	//**************************************************************
		
	Bomb bomb; // c4 (bomb) (David Goodwin - 11/4/14)
	Ammo ammo; // ammo for player (David Goodwin - 11/4/14)
	//*************************************************************
	
	Mix_Chunk *finish_wav;	//sound for crossing finish line
	
	int xVel;
	int yVel;	

public:
	Level_1();
	~Level_1();
	void logic();
	void render();
	void handle_event();

	void load_maze();
};

Level_1::Level_1()
{
	finish_wav = Mix_LoadWAV("Finish.wav");
	gameBack = loadTexture("game_back.png");
	load_maze();
	player.init(320, 560);

	//UPDATED : 11/10/14 - Eliot Holland*******************************
	timer.init( 710, 180 );
	//*****************************************************************

	//MOD : 11/4/14 - Eliot Holland - Original - David Goodwin**********
	enemy[0].init(340,180,1,1);			//initialize enemy objects
	enemy[1].init(700,400,1,1);
	enemy[2].init(500,380,1,1);
	//******************************************************************

	bomb.init(480,380); // Initialization of the bomb c4 (bomb) (David Goodwin - 11/4/14)
	ammo.init(500,380); // Initialization of ammo for player (David Goodwin - 11/4/14)
	
	boundaries.x = 320;
	boundaries.y = 180;
	boundaries.w = 720;
	boundaries.h = 580;

	xVel = 0;						//resets velocity
	yVel = 0;
}//end Level_1()

Level_1::~Level_1()
{
	SDL_DestroyTexture (gameBack);
	gameBack = NULL;
	Mix_FreeChunk(finish_wav);
}//end ~Level_1()

void Level_1::logic()
{
	timer.calculate();		//Get the time

	//*******************
	//	PLAYER MOVEMENT	*
	//*******************

	// X Movement
	player.player_box.x += xVel;			//move player along x axis

	if ((player.player_box.x < boundaries.x)		//If colliding
	|| (player.player_box.x	+ player.player_box.w   //with boundaries
	> boundaries.w))
	{
		player.player_box.x -= xVel;			//stop movement
	}//end if
	
	for (int i = 0; i < 164; ++i)				//for every brick wall
	{											//check for collision
		switch (check_collision(player.player_box,
								brick[i].brick_wall))
		{
		case true: 
			{
				player.player_box.x -= xVel;	//stop movement
				break;
			}//end case
		case false:
			{
				break;
			}//end case
		}//end switch
	}//end for

	// Y Movement
	player.player_box.y += yVel;			//move player along y axis

	if ((player.player_box.y < boundaries.y)		//if colliding
	|| (player.player_box.y + player.player_box.h	//with boundaries
	> boundaries.h))
	{
		player.player_box.y -= yVel;		//stop movement
	}//end if
	for (int i = 0; i < 164; ++i)			//for every brick wall
	{										//check collision
		switch (check_collision(player.player_box, 
								brick[i].brick_wall))
		{
		case true: 
			{
				player.player_box.y -= yVel;//stop movement
				break;
			}//end case
		case false:
			{
				break;						//no collision
			}//end case
		}//end switch
	}//end for

//MOD : 11/4/14 - Eliot Holland - Original - David Goodwin**********
	for (int i = 0; i < 3; ++i)				//for every enemy
	{										//check for collision
		switch (check_collision(player.player_box,	//with player
								enemy[i].ai_box))
		{
		case true:					//if yes
			{
				player.reset();		//reset player
				enemy[i].reset();	//reset enemy
				break;
			}//end case
		case false:					//if no
			{
				break;	//exit loop
			}//end case
		}//end switch
	}//end for
//*******************************************************************	
}

void Level_1::render()
{
	apply_surface(gameBack, NULL);	//show background
	timer.show();					//show clock
	player.show();					//show player

	//MOD : 11/4/14 - Eliot Holland - Original - David Goodwin************
	for (int i = 0; i < 3; ++i) enemy[i].show();  //show every enemy
	//********************************************************************
	for (int i = 0; i < 164; ++i) brick[i].show(); //show maze

	bomb.show(); // render the c4 (bomb) (David Goodwin - 11/4/14)
	ammo.show(); // render ammo for player (David Goodwin - 11/4/14)
}//end render

void Level_1::handle_event()
{
	int counter = 0;
	int x = 0, y = 0;				//mouse events

	xVel = 0;						//resets velocity every frame
	yVel = 0;
	
//MOD : 11/4/14 - Eliot Holland - Original - David Goodwin************
	for (int i = 0; i < 3; ++i)		//for every enemy
	{								//handle events
		enemy[i].handle_event(	boundaries,
								brick,
								player.player_box.x,
								player.player_box.y);
	}//end for
//********************************************************************

//UPDATED 11/10/14 - Eliot Holland************************************
	SDL_Delay(5);   //slows down movement in milliseconds
	//movement controls (arrows)
	if( currentKeyStates[ SDL_SCANCODE_UP] )	yVel -= 1;	//end if
	if( currentKeyStates[ SDL_SCANCODE_DOWN] )	yVel += 1;	//end if		
	if( currentKeyStates[ SDL_SCANCODE_LEFT] )	xVel -= 1;	//end if		
	if( currentKeyStates[ SDL_SCANCODE_RIGHT] ) xVel += 1;	//end if

	//movement controls (WASD)
	if( currentKeyStates[ SDL_SCANCODE_W] )	yVel -= 1;	//end if
	if( currentKeyStates[ SDL_SCANCODE_S] )	yVel += 1;	//end if		
	if( currentKeyStates[ SDL_SCANCODE_A] )	xVel -= 1;	//end if		
	if( currentKeyStates[ SDL_SCANCODE_D] ) xVel += 1;	//end if

	if( currentKeyStates[ SDL_SCANCODE_RETURN] )
	{
		set_next_state(STATE_LVL2);		//go to level 2
	}//end if
	if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
	{
		set_next_state(STATE_MENU);		//back to menu
	}//end if


	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) set_next_state(STATE_EXIT);	//quit
	}//end while

	if( check_collision( player.player_box, timer.finish_box ))
	{
		if (Mix_PlayChannel(-1, finish_wav, 0) == -1)	//play sound clip
		{
			set_next_state(STATE_EXIT);		//check for error
		}//end if

		SDL_Delay(2500);
		set_next_state( STATE_OVER );
	}//end if
//********************************************************************
}//end hadle_event()

void Level_1::load_maze()
{
	//column 1     x ,  y			//column 2
	brick[0].init(320, 240);		brick[10].init(340, 200);
	brick[1].init(320, 260);		brick[11].init(340, 240);	
	brick[2].init(320, 280);		brick[12].init(340, 320);
	brick[3].init(320, 360);		brick[13].init(340, 360);
	brick[4].init(320, 380);		brick[14].init(340, 420);
	brick[5].init(320, 420);		brick[15].init(340, 500);
	brick[6].init(320, 440);		brick[16].init(340, 540);
	brick[7].init(320, 460);		brick[17].init(340, 560);
	brick[8].init(320, 480);		
	brick[9].init(320, 500);

	//column 3						//column 4
	brick[18].init(360, 180);		brick[26].init(380, 180);
	brick[19].init(360, 200);		brick[27].init(380, 220);
	brick[20].init(360, 280);		brick[28].init(380, 260);
	brick[21].init(360, 320);		brick[29].init(380, 280);
	brick[22].init(360, 360);		brick[30].init(380, 440);
	brick[23].init(360, 400);		brick[31].init(380, 460);
	brick[24].init(360, 460);		brick[32].init(380, 520);
	brick[25].init(360, 500);		brick[33].init(380, 560);

	//column 5						//column 6
	brick[34].init(400, 180);		brick[41].init(420, 180);
	brick[35].init(400, 260);		brick[42].init(420, 220);
	brick[36].init(400, 320);		brick[43].init(420, 240);
	brick[37].init(400, 360);		brick[44].init(420, 260);
	brick[38].init(400, 400);		brick[45].init(420, 300);
	brick[39].init(400, 460);		brick[46].init(420, 320);
	brick[40].init(400, 480);		brick[47].init(420, 340);
									brick[48].init(420, 400);
									brick[49].init(420, 420);
									brick[50].init(420, 520);
									brick[51].init(420, 540);

	//column 7						//column 8
	brick[52].init(440, 380);		brick[56].init(460, 200);
	brick[53].init(440, 400);		brick[57].init(460, 240);
	brick[54].init(440, 460);		brick[58].init(460, 280);
	brick[55].init(440, 480);		brick[59].init(460, 320);
									brick[60].init(460, 340);
									brick[61].init(460, 440);
									brick[62].init(460, 460);
									brick[63].init(460, 480);
									brick[64].init(460, 500);
									brick[65].init(460, 540);

	//column 9						//column 10	
	brick[66].init(480, 200);		brick[74].init(500, 260);
	brick[67].init(480, 220);		brick[75].init(500, 280);
	brick[68].init(480, 280);		brick[76].init(500, 300);
	brick[69].init(480, 340);		brick[77].init(500, 340);
	brick[70].init(480, 360);		brick[78].init(500, 400);
	brick[71].init(480, 400);		brick[79].init(500, 420);
	brick[72].init(480, 460);		brick[80].init(500, 500);
	brick[73].init(480, 540);		brick[81].init(500, 520);
									brick[82].init(500, 540);
									brick[83].init(500, 560);

	//column 11						//column 12
	brick[84].init(520, 180);		brick[91].init(540, 180);
	brick[85].init(520, 200);		brick[92].init(540, 200);
	brick[86].init(520, 240);		brick[93].init(540, 300);
	brick[87].init(520, 260);		brick[94].init(540, 320);
	brick[88].init(520, 360);		brick[95].init(540, 360);
	brick[89].init(520, 460);		brick[96].init(540, 380);
	brick[90].init(520, 520);		brick[97].init(540, 400);
									brick[98].init(540, 440);
									brick[99].init(540, 460);
									brick[100].init(540, 480);
									brick[101].init(540, 560);

	//column 13						//column 14
	brick[102].init(560, 180);		brick[109].init(580, 220);
	brick[103].init(560, 240);		brick[110].init(580, 280);
	brick[104].init(560, 280);		brick[111].init(580, 320);
	brick[105].init(560, 380);		brick[112].init(580, 340);
	brick[106].init(560, 520);		brick[113].init(580, 420);
	brick[107].init(560, 540);		brick[114].init(580, 440);
	brick[108].init(560, 560);		brick[115].init(580, 480);
									brick[116].init(580, 500);
									brick[117].init(580, 520);

	//column 15						//column 16
	brick[118].init(600, 200);		brick[126].init(620, 240);
	brick[119].init(600, 260);		brick[127].init(620, 300);
	brick[120].init(600, 280);		brick[128].init(620, 440);
	brick[121].init(600, 320);		brick[129].init(620, 460);
	brick[122].init(600, 340);		brick[130].init(620, 480);
	brick[123].init(600, 360);		brick[131].init(620, 500);
	brick[124].init(600, 380);		brick[132].init(620, 520);
	brick[125].init(600, 560);		brick[133].init(620, 560);

	//column 17						//column 18
	brick[134].init(640, 180);		brick[143].init(660, 180);
	brick[135].init(640, 220);		brick[144].init(660, 260);
	brick[136].init(640, 280);		brick[145].init(660, 280);
	brick[137].init(640, 340);		brick[146].init(660, 320);
	brick[138].init(640, 380);		brick[147].init(660, 340);
	brick[139].init(640, 420);		brick[148].init(660, 440);
	brick[140].init(640, 440);		brick[149].init(660, 480);
	brick[141].init(640, 520);		
	brick[142].init(640, 560);

	//column 19						//column 20
	brick[150].init(680, 180);		brick[160].init(700, 220);
	brick[151].init(680, 220);		brick[161].init(700, 300);
	brick[152].init(680, 260);		brick[162].init(700, 380);
	brick[153].init(680, 340);		brick[163].init(700, 480);
	brick[154].init(680, 380);		
	brick[155].init(680, 400);		
	brick[156].init(680, 440);
	brick[157].init(680, 480);		
	brick[158].init(680, 520);		
	brick[159].init(680, 540);
}

#endif