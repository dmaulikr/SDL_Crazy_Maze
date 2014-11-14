#pragma once
#ifndef _MENU_H_INCLUDED_
#define _MENU_H_INCLUDED_

#include "State.h"
#include "Button.h"

class Menu : public State
{
private:
	SDL_Texture *mainBack;
	SDL_Texture *exit;
	SDL_Texture *exit_o;
	SDL_Texture *play;
	SDL_Texture *play_o;
	SDL_Texture *help;
	SDL_Texture	*help_o;
	
	Button play_b;
	Button help_b;
	Button exit_b;

public:
	Menu();						//Constructor
	~Menu();					//Destructor
	void logic();				//any code not event/render related
	void render();				//render the state
	void handle_event();
};

Menu::Menu()
{
	mainBack =	loadTexture("g_back.png");

	//Load button textures
	exit =		loadTexture("Exit.png");
	exit_o =	loadTexture("Exito.png");
	play =		loadTexture("Play.png");
	play_o =	loadTexture("Playo.png");
	help =		loadTexture("Help.png");
	help_o =	loadTexture("Helpo.png");

	//Instantiate Button objects
	play_b.init(850, 300, 100, 50, play);
	help_b.init(850, 400, 100, 50, help);
	exit_b.init(850, 500, 100, 50, exit);	
}

Menu::~Menu()
{
	SDL_DestroyTexture (mainBack);
	SDL_DestroyTexture (exit);
	SDL_DestroyTexture (exit_o);
	SDL_DestroyTexture (play);
	SDL_DestroyTexture (play_o);
	SDL_DestroyTexture (help);
	SDL_DestroyTexture (help_o);

	mainBack =	NULL;
	exit =		NULL;
	exit_o =	NULL;
	play =		NULL;
	play_o =	NULL;
	help =		NULL;
	help_o =	NULL;
}
void Menu::logic()
{
	
}
void Menu::render()
{
	apply_surface(mainBack, NULL);
	exit_b.show();
	play_b.show();
	help_b.show();
}
void Menu::handle_event()
{
	int x = 0, y = 0;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) set_next_state(STATE_EXIT);									//window X'd out

		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)											//escape key pressed
			{
				set_next_state(STATE_EXIT);
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;								
				y = event.button.y;


				if ((x > play_b.box.x)															//Play Button
					&& (x < play_b.box.x + play_b.box.w)
					&& (y > play_b.box.y)
					&& (y < play_b.box.y + play_b.box.h))	play_b.sprite = play_o;

				else if ((x > exit_b.box.x)														//Exit Button
					&& (x < exit_b.box.x + exit_b.box.w)
					&& (y > exit_b.box.y)
					&& (y < exit_b.box.y + exit_b.box.h))	exit_b.sprite = exit_o;
				
				else if ((x > help_b.box.x)														//Help Button
					&& (x < help_b.box.x + help_b.box.w)
					&& (y > help_b.box.y)
					&& (y < help_b.box.y + help_b.box.h))	help_b.sprite = help_o;

			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;
				
				if ((x > play_b.box.x)
					&& (x < play_b.box.x + play_b.box.w)
					&& (y > play_b.box.y)
					&& (y < play_b.box.y + play_b.box.h))	set_next_state(STATE_LVL1);
				
				if ((x > exit_b.box.x)
					&& (x < exit_b.box.x + exit_b.box.w)
					&& (y > exit_b.box.y)
					&& (y < exit_b.box.y + exit_b.box.h))	set_next_state(STATE_EXIT);

				else if ((x > help_b.box.x)														//Help Button
					&& (x < help_b.box.x + help_b.box.w)
					&& (y > help_b.box.y)
					&& (y < help_b.box.y + help_b.box.h))	set_next_state(STATE_HELP);

				else
				{
					play_b.sprite = play;
					exit_b.sprite = exit;
					help_b.sprite = help;
				}
			}
		}
	}
}


#endif