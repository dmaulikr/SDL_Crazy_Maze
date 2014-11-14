#pragma once
#ifndef _LEVEL_3_H_INCLUDED_
#define _LEVEL_3_H_INCLUDED_

#include "State.h"
#include "Square.h"
#include "Brick.h"
#include "Player.h"
#include "AI.h"


class Level_3 : public State
{
private:
	SDL_Texture *gameBack;
	SDL_Rect boundaries;
	SDL_Rect plyr_rect;

	Brick brick[274];
	Player player;

	int xVel;
	int yVel;	

public:
	Level_3();
	~Level_3();
	void logic();
	void render();
	void handle_event();
	void load_maze();
};

Level_3::Level_3()
{
	gameBack = loadTexture("game_back_2_3.png");
	load_maze();
	player.init(320, 660);

	boundaries.x = 320;
	boundaries.y = 180;
	boundaries.w = 820;
	boundaries.h = 680;
}

Level_3::~Level_3()
{
	SDL_DestroyTexture (gameBack);

	gameBack = NULL;
}

void Level_3::logic()
{
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
	
	for (int i = 0; i < 274; ++i)				//for every brick wall
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
	for (int i = 0; i < 274; ++i)			//for every brick wall
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
}//end logic()

void Level_3::render()
{
	apply_surface(gameBack, NULL);
	player.show();

	for (int i = 0; i < 274; ++i) brick[i].show();
}

void Level_3::handle_event()
{
	int counter = 0;
	int x = 0, y = 0;				//mouse events

	xVel = 0;						//resets velocity every frame
	yVel = 0;
	
	
	/*************
	*  EXIT GAME *
	**************/
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) set_next_state(STATE_EXIT);

		if (event.type == SDL_KEYDOWN)
		{
	/************************
	*	MOVEMENT CONTROLS	*
	*************************/
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:		yVel -= 5; break;
			case SDLK_DOWN:		yVel += 5; break;
			case SDLK_LEFT:		xVel -= 5; break;
			case SDLK_RIGHT:	xVel += 5; break;

			//********************************************************************************************************************************
			// AI Movement {for testing purposes} - (David Goodwin 10/23/14)  This section is no longer needed, however if we wanted to add a second player we could use these controlls.
			/*case SDLK_w:		ai_yVel -= 5; break;
			case SDLK_s:		ai_yVel += 5; break;
			case SDLK_a:		ai_xVel -= 5; break;
			case SDLK_d:		ai_xVel += 5; break;*/
			//********************************************************************************************************************************

			case SDLK_RETURN:	set_next_state(STATE_OVER);
			//exit to menu
			//case SDLK_ESCAPE:	set_next_state(STATE_MENU);
			}
		}
	}
}

void Level_3::load_maze()
{
	//column 1     x , y
	brick[0].init(320, 200);
	brick[1].init(320, 240);
	brick[2].init(320, 300);
	brick[3].init(320, 340);
	brick[4].init(320, 380);
	brick[5].init(320, 400);
	brick[6].init(320, 420);
	brick[7].init(320, 500);
	brick[8].init(320, 520);
	brick[9].init(320, 540);
	brick[10].init(320, 560);
	brick[11].init(320, 600);
	//column 2
	brick[12].init(340, 200);
	brick[13].init(340, 300);
	brick[14].init(340, 340);
	brick[15].init(340, 460);
	brick[16].init(340, 520);
	brick[17].init(340, 540);
	brick[18].init(340, 560);
	brick[19].init(340, 600);
	brick[20].init(340, 640);
	//column 3
	brick[21].init(360, 260);
	brick[22].init(360, 300);
	brick[23].init(360, 340);
	brick[24].init(360, 360);
	brick[25].init(360, 400);
	brick[26].init(360, 440);
	brick[27].init(360, 460);
	brick[28].init(360, 480);
	brick[29].init(360, 540);
	brick[30].init(360, 560);
	brick[31].init(360, 600);
	brick[32].init(360, 620);
	brick[33].init(360, 640);
	//column 4
	brick[34].init(380, 200);
	brick[35].init(380, 260);
	brick[36].init(380, 300);
	brick[37].init(380, 360);
	brick[38].init(380, 400);
	brick[39].init(380, 440);
	brick[40].init(380, 480);
	brick[41].init(380, 500);
	brick[42].init(380, 560);
	brick[43].init(380, 640);
	//column 5
	brick[44].init(400, 200);
	brick[45].init(400, 260);
	brick[46].init(400, 360);
	brick[47].init(400, 400);
	brick[48].init(400, 440);
	brick[49].init(400, 500);
	brick[50].init(400, 520);
	brick[51].init(400, 560);
	brick[52].init(400, 580);
	brick[53].init(400, 600);
	brick[54].init(400, 640);
	//column 6
	brick[55].init(420, 200);
	brick[56].init(420, 260);
	brick[57].init(420, 320);
	brick[58].init(420, 360);
	brick[59].init(420, 400);
	brick[60].init(420, 460);
	brick[61].init(420, 520);
	brick[62].init(420, 600);
	brick[63].init(420, 640);
	//column 7
	brick[64].init(440, 200);
	brick[65].init(440, 260);
	brick[66].init(440, 320);
	brick[67].init(440, 360);
	brick[68].init(440, 420);
	brick[69].init(440, 480);
	brick[70].init(440, 520);
	brick[71].init(440, 560);
	brick[72].init(440, 600);
	brick[73].init(440, 640);
	//column 8
	brick[74].init(460, 200);
	brick[75].init(460, 260);
	brick[76].init(460, 320);
	brick[77].init(460, 380);
	brick[78].init(460, 440);
	brick[79].init(460, 480);
	brick[80].init(460, 520);
	brick[81].init(460, 560);
	brick[82].init(460, 600);
	brick[83].init(460, 640);
	//column 9
	brick[84].init(480, 200);
	brick[85].init(480, 280);
	brick[86].init(480, 320);
	brick[87].init(480, 380);
	brick[88].init(480, 400);
	brick[89].init(480, 440);
	brick[90].init(480, 480);
	brick[91].init(480, 520);
	brick[92].init(480, 560);
	brick[93].init(480, 600);
	brick[94].init(480, 640);
	//column 10
	brick[95].init(500, 200);
	brick[96].init(500, 240);
	brick[97].init(500, 260);
	brick[98].init(500, 280);
	brick[99].init(500, 320);
	brick[100].init(500, 400);
	brick[101].init(500, 440);
	brick[102].init(500, 480);
	brick[103].init(500, 520);
	brick[104].init(500, 560);
	brick[105].init(500, 600);
	//column 11
	brick[106].init(520, 220);
	brick[107].init(520, 280);
	brick[108].init(520, 320);
	brick[109].init(520, 360);
	brick[110].init(520, 480);
	brick[111].init(520, 520);
	brick[112].init(520, 560);
	brick[113].init(520, 600);
	brick[114].init(520, 640);
	//column 12
	brick[115].init(540, 180);
	brick[116].init(540, 220);
	brick[117].init(540, 280);
	brick[118].init(540, 320);
	brick[119].init(540, 360);
	brick[120].init(540, 440);
	brick[121].init(540, 480);
	brick[122].init(540, 520);
	brick[123].init(540, 560);
	brick[124].init(540, 600);
	brick[125].init(540, 640);
	//column 13
	brick[126].init(560, 180);
	brick[127].init(560, 220);
	brick[128].init(560, 280);
	brick[129].init(560, 320);
	brick[130].init(560, 400);
	brick[131].init(560, 440);
	brick[132].init(560, 480);
	brick[133].init(560, 560);
	brick[134].init(560, 640);
	//column 14
	brick[135].init(580, 180);
	brick[136].init(580, 220);
	brick[137].init(580, 320);
	brick[138].init(580, 380);
	brick[139].init(580, 440);
	brick[140].init(580, 480);
	brick[141].init(580, 520);
	brick[142].init(580, 560);
	brick[143].init(580, 620);
	brick[144].init(580, 640);
	//column 15
	brick[145].init(600, 180);
	brick[146].init(600, 220);
	brick[147].init(600, 300);
	brick[148].init(600, 360);
	brick[149].init(600, 420);
	brick[150].init(600, 480);
	brick[151].init(600, 520);
	brick[152].init(600, 560);
	brick[153].init(600, 600);
	brick[154].init(600, 620);
	brick[155].init(600, 640);
	//column 16 
	brick[156].init(620, 180);
	brick[157].init(620, 220);
	brick[158].init(620, 280);
	brick[159].init(620, 340);
	brick[160].init(620, 400);
	brick[161].init(620, 460);
	brick[162].init(620, 480);
	brick[163].init(620, 520);
	brick[164].init(620, 560);
	brick[165].init(620, 600);
	//column 17
	brick[166].init(640, 180);
	brick[167].init(640, 220);
	brick[168].init(640, 260);
	brick[169].init(640, 320);
	brick[170].init(640, 380);
	brick[171].init(640, 440);
	brick[172].init(640, 460);
	brick[173].init(640, 480);
	brick[174].init(640, 520);
	brick[175].init(640, 560);
	brick[176].init(640, 600);
	brick[177].init(640, 640);
	//column 18
	brick[178].init(660, 180);
	brick[179].init(660, 240);
	brick[180].init(660, 300);
	brick[181].init(660, 360);
	brick[182].init(660, 420);
	brick[183].init(660, 440);
	brick[184].init(660, 460);
	brick[185].init(660, 480);
	brick[186].init(660, 560);
	brick[187].init(660, 600);
	brick[188].init(660, 640);
	//column 19
	brick[189].init(680, 180);
	brick[190].init(680, 200);
	brick[191].init(680, 240);
	brick[192].init(680, 280);
	brick[193].init(680, 300);
	brick[194].init(680, 320);
	brick[195].init(680, 340);
	brick[196].init(680, 360);
	brick[197].init(680, 400);
	brick[198].init(680, 420);
	brick[199].init(680, 440);
	brick[200].init(680, 460);
	brick[201].init(680, 480);
	brick[202].init(680, 520);
	brick[203].init(680, 600);
	brick[204].init(680, 640);
	//column 20
	brick[205].init(700, 200);
	brick[206].init(700, 240);
	brick[207].init(700, 280);
	brick[208].init(700, 360);
	brick[209].init(700, 400);
	brick[210].init(700, 480);
	brick[211].init(700, 520);
	brick[212].init(700, 560);
	brick[213].init(700, 580);
	brick[214].init(700, 600);
	brick[215].init(700, 640);
	//column 21
	brick[216].init(720, 240);
	brick[217].init(720, 280);
	brick[218].init(720, 320);
	brick[219].init(720, 360);
	brick[220].init(720, 400);
	brick[221].init(720, 440);
	brick[222].init(720, 480);
	brick[223].init(720, 520);
	brick[224].init(720, 560);
	brick[225].init(720, 640);
	//column 22
	brick[226].init(740, 200);
	brick[227].init(740, 240);
	brick[228].init(740, 280);
	brick[229].init(740, 340);
	brick[230].init(740, 360);
	brick[231].init(740, 400);
	brick[232].init(740, 440);
	brick[233].init(740, 480);
	brick[234].init(740, 520);
	brick[235].init(740, 560);
	brick[236].init(740, 600);
	brick[237].init(740, 620);
	brick[238].init(740, 640);
	//column 23
	brick[239].init(760, 180);
	brick[240].init(760, 200);
	brick[241].init(760, 240);
	brick[242].init(760, 280);
	brick[243].init(760, 300);
	brick[244].init(760, 340);
	brick[245].init(760, 360);
	brick[246].init(760, 400);
	brick[247].init(760, 440);
	brick[248].init(760, 480);
	brick[249].init(760, 520);
	brick[250].init(760, 560);
	brick[251].init(760, 600);
	brick[252].init(760, 640);
	//column 24
	brick[253].init(780, 180);
	brick[254].init(780, 200);
	brick[255].init(780, 240);
	brick[256].init(780, 300);
	brick[257].init(780, 360);
	brick[258].init(780, 400);
	brick[259].init(780, 440);
	brick[260].init(780, 520);
	brick[261].init(780, 560);
	brick[262].init(780, 600);
	//column 25
	brick[263].init(800, 180);
	brick[264].init(800, 200);
	brick[265].init(800, 240);
	brick[266].init(800, 320);
	brick[267].init(800, 400);
	brick[268].init(800, 440);
	brick[269].init(800, 500);
	brick[270].init(800, 560);
	brick[271].init(800, 600);
	brick[272].init(800, 620);
	brick[273].init(800, 640);

	
}

#endif