#pragma once
#ifndef _LEVEL_2_H_INCLUDED_
#define _LEVEL_2_H_INCLUDED_

#include "State.h"
#include "Square.h"
#include "Brick.h"
#include "Player.h"

class Level_2 : public State
{
private:
	SDL_Texture *gameBack;
	SDL_Rect boundaries;
	SDL_Rect plyr_rect;

	Brick brick[265];
	Player player;

	int xVel;
	int yVel;	

public:
	Level_2();
	~Level_2();
	void logic();
	void render();
	void handle_event();
	void load_maze();
};

Level_2::Level_2()
{
	gameBack = loadTexture("game_back_2_3.png");
	load_maze();
	player.init(320, 660);

	boundaries.x = 320;
	boundaries.y = 180;
	boundaries.w = 820; //Eliot Holland
	boundaries.h = 680; //Eliot Holland
}

Level_2::~Level_2()
{
	SDL_DestroyTexture (gameBack);

	gameBack = NULL;
}

void Level_2::logic()
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
	
	for (int i = 0; i < 265; ++i)				//for every brick wall
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
	for (int i = 0; i < 265; ++i)			//for every brick wall
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
}

void Level_2::render()
{
	apply_surface(gameBack, NULL);
	player.show();

	for (int i = 0; i < 265; ++i) brick[i].show();
}

void Level_2::handle_event()
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
			
			case SDLK_RETURN:	set_next_state(STATE_LVL3);
			//exit to menu
			//case SDLK_ESCAPE:	set_next_state(STATE_MENU);
			}
		}
	}
}

void Level_2::load_maze()
{
	//column 1     x ,  y		
	brick[0].init(320, 260);
	brick[1].init(320, 300);
	brick[2].init(320, 320);
	brick[3].init(320, 360);
	brick[4].init(320, 400);
	brick[5].init(320, 440);
	brick[6].init(320, 520);
	brick[7].init(320, 560);
	brick[8].init(320, 620);
	//column 2
	brick[9].init(340, 180);
	brick[10].init(340, 200);
	brick[11].init(340, 220);
	brick[12].init(340, 260);
	brick[13].init(340, 300);
	brick[14].init(340, 320);
	brick[15].init(340, 360);
	brick[16].init(340, 400);
	brick[17].init(340, 440);
	brick[18].init(340, 480);
	brick[19].init(340, 560);
	brick[20].init(340, 600);
	brick[21].init(340, 620);
	brick[22].init(340, 660);
	//coulumn 3
	brick[23].init(360, 180);
	brick[24].init(360, 200);
	brick[25].init(360, 220);
	brick[26].init(360, 260);
	brick[27].init(360, 320);
	brick[28].init(360, 400);
	brick[29].init(360, 480);
	brick[30].init(360, 520);
	brick[31].init(360, 560);
	brick[32].init(360, 660);
	//column 4
	brick[33].init(380, 260);
	brick[34].init(380, 320);
	brick[35].init(380, 340);
	brick[36].init(380, 360);
	brick[37].init(380, 400);
	brick[38].init(380, 420);
	brick[39].init(380, 460);
	brick[40].init(380, 520);
	brick[41].init(380, 560);
	brick[42].init(380, 600);
	brick[43].init(380, 640);
	brick[44].init(380, 660);
	//column 5
	brick[45].init(400, 200);
	brick[46].init(400, 240);
	brick[47].init(400, 260);
	brick[48].init(400, 340);
	brick[49].init(400, 360);
	brick[50].init(400, 400);
	brick[51].init(400, 420);
	brick[52].init(400, 460);
	brick[53].init(400, 520);
	brick[54].init(400, 560);
	brick[55].init(400, 600);
	brick[56].init(400, 640);
	//column 6
	brick[57].init(420, 200);
	brick[58].init(420, 240);
	brick[59].init(420, 300);
	brick[60].init(420, 360);
	brick[61].init(420, 400);
	brick[62].init(420, 420);
	brick[63].init(420, 460);
	brick[64].init(420, 520);
	brick[65].init(420, 600);
	//column 7
	brick[66].init(440, 200);
	brick[67].init(440, 240);
	brick[68].init(440, 280);
	brick[69].init(440, 300);
	brick[70].init(440, 320);
	brick[71].init(440, 400);
	brick[72].init(440, 420);
	brick[73].init(440, 460);
	brick[74].init(440, 520);
	brick[75].init(440, 560);
	brick[76].init(440, 600);
	brick[77].init(440, 640);
	brick[78].init(440, 660);
	//column 8
	brick[79].init(460, 200);
	brick[80].init(460, 240);
	brick[81].init(460, 340);
	brick[82].init(460, 400);
	brick[83].init(460, 460);
	brick[84].init(460, 520);
	brick[85].init(460, 560);
	brick[86].init(460, 600);
	brick[87].init(460, 620);
	brick[88].init(460, 640);
	//column 9
	brick[89].init(480, 200);
	brick[90].init(480, 240);
	brick[91].init(480, 260);
	brick[92].init(480, 280);
	brick[93].init(480, 300);
	brick[94].init(480, 320);
	brick[95].init(480, 340);
	brick[96].init(480, 400);
	brick[97].init(480, 520);
	brick[98].init(480, 560);
	brick[99].init(480, 600);
	//column 10
	brick[100].init(500, 200);
	brick[101].init(500, 340);
	brick[102].init(500, 400);
	brick[103].init(500, 480);
	brick[104].init(500, 520);
	brick[105].init(500, 560);
	brick[106].init(500, 600);
	brick[107].init(500, 640);
	//column 11
	brick[108].init(520, 220);
	brick[109].init(520, 300);
	brick[110].init(520, 340);
	brick[111].init(520, 400);
	brick[112].init(520, 460);
	brick[113].init(520, 520);
	brick[114].init(520, 560);
	brick[115].init(520, 580);
	brick[116].init(520, 640);
	brick[117].init(520, 660);
	//column 12
	brick[118].init(540, 260);
	brick[119].init(540, 300);
	brick[120].init(540, 340);
	brick[121].init(540, 400);
	brick[122].init(540, 420);
	brick[123].init(540, 460);
	brick[124].init(540, 620);
	brick[125].init(540, 640);
	//column 13
	brick[126].init(560, 200);
	brick[127].init(560, 240);
	brick[128].init(560, 300);
	brick[129].init(560, 340);
	brick[130].init(560, 400);
	brick[131].init(560, 420);
	brick[132].init(560, 460);
	brick[133].init(560, 480);
	brick[134].init(560, 500);
	brick[135].init(560, 520);
	brick[136].init(560, 560);
	brick[137].init(560, 580);
	brick[138].init(560, 620);
	//column 14
	brick[139].init(580, 200);
	brick[140].init(580, 240);
	brick[141].init(580, 300);
	brick[142].init(580, 340);
	brick[143].init(580, 400);
	brick[144].init(580, 420);
	brick[145].init(580, 460);
	brick[146].init(580, 520);
	brick[147].init(580, 560);
	brick[148].init(580, 620);
	brick[149].init(580, 660);
	//column 15
	brick[150].init(600, 180);
	brick[151].init(600, 200);
	brick[152].init(600, 240);
	brick[153].init(600, 380);
	brick[154].init(600, 400);
	brick[155].init(600, 420);
	brick[156].init(600, 460);
	brick[157].init(600, 520);
	brick[158].init(600, 560);
	brick[159].init(600, 600);
	brick[160].init(600, 620);
	brick[161].init(600, 660);
	//column 16
	brick[162].init(620, 200);
	brick[163].init(620, 240);
	brick[164].init(620, 280);
	brick[165].init(620, 380);
	brick[166].init(620, 400);
	brick[167].init(620, 420);
	brick[168].init(620, 460);
	brick[169].init(620, 520);
	brick[170].init(620, 560);
	brick[171].init(620, 620);
	brick[172].init(620, 660);
	//column 17
	brick[173].init(640, 240);
	brick[174].init(640, 340);
	brick[175].init(640, 400);
	brick[176].init(640, 420);
	brick[177].init(640, 460);
	brick[178].init(640, 520);
	brick[179].init(640, 560);
	brick[180].init(640, 580);
	brick[181].init(640, 620);
	brick[182].init(640, 660);
	//column 18
	brick[183].init(660, 240);
	brick[184].init(660, 300);
	brick[185].init(660, 340);
	brick[186].init(660, 400);
	brick[187].init(660, 420);
	brick[188].init(660, 460);
	brick[189].init(660, 500);
	brick[190].init(660, 580);
	brick[191].init(660, 620);
	brick[192].init(660, 660);
	//column 19
	brick[193].init(680, 220);
	brick[194].init(680, 240);
	brick[195].init(680, 300);
	brick[196].init(680, 340);
	brick[197].init(680, 400);
	brick[198].init(680, 420);
	brick[199].init(680, 460);
	brick[200].init(680, 500);
	brick[201].init(680, 540);
	brick[202].init(680, 580);
	//column 20
	brick[203].init(700, 200);
	brick[204].init(700, 280);
	brick[205].init(700, 340);
	brick[206].init(700, 400);
	brick[207].init(700, 420);
	brick[208].init(700, 460);
	brick[209].init(700, 500);
	brick[210].init(700, 540);
	brick[211].init(700, 580);
	brick[212].init(700, 620);
	brick[213].init(700, 640);
	//column 21
	brick[214].init(720, 200);
	brick[215].init(720, 280);
	brick[216].init(720, 340);
	brick[217].init(720, 400);
	brick[218].init(720, 420);
	brick[219].init(720, 460);
	brick[220].init(720, 500);
	brick[221].init(720, 540);
	brick[222].init(720, 580);
	brick[223].init(720, 640);
	//column 22
	brick[224].init(740, 200);
	brick[225].init(740, 260);
	brick[226].init(740, 280);
	brick[227].init(740, 300);
	brick[228].init(740, 320);
	brick[229].init(740, 340);
	brick[230].init(740, 400);
	brick[231].init(740, 420);
	brick[232].init(740, 460);
	brick[233].init(740, 500);
	brick[234].init(740, 540);
	brick[235].init(740, 560);
	brick[236].init(740, 600);
	brick[237].init(740, 620);
	brick[238].init(740, 640);
	//column 23
	brick[239].init(760, 340);
	brick[240].init(760, 400);
	brick[241].init(760, 460);
	brick[242].init(760, 500);
	brick[243].init(760, 540);
	brick[244].init(760, 600);
	brick[245].init(760, 640);
	//column 24
	brick[246].init(780, 200);
	brick[247].init(780, 240);
	brick[248].init(780, 260);
	brick[249].init(780, 280);
	brick[250].init(780, 320);
	brick[251].init(780, 340);
	brick[252].init(780, 440);
	brick[253].init(780, 460);
	brick[254].init(780, 500);
	brick[255].init(780, 580);
	brick[256].init(780, 600);
	brick[257].init(780, 640);
	//column 25
	brick[258].init(800, 200);
	brick[259].init(800, 240);
	brick[260].init(800, 340);
	brick[261].init(800, 420);
	brick[262].init(800, 500);
	brick[263].init(800, 540);
	brick[264].init(800, 640);

}

#endif