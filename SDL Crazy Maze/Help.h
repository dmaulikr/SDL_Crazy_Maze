#pragma once
#ifndef _HELP_H_INCLUDED_
#define _HELP_H_INCLUDED_

#include "State.h"
#include "Button.h"

class Help : public State
{
private:
	SDL_Texture *helpBack;
	SDL_Texture *menu;
	SDL_Texture *menuo;
	SDL_Texture *exit;
	SDL_Texture *exito;

	Button menu_B;
	Button exit_B;
public:
	Help();
	~Help();
	void logic();
	void render();
	void handle_event();
};

Help::Help()
{
	helpBack =	loadTexture("help_back.png");
	menu =		loadTexture("Menu.png");
	menuo =		loadTexture("Menuo.png");
	exit =		loadTexture("Exit.png");
	exito =		loadTexture("Exito.png");

	menu_B.init(850, 300, 100, 50, menu);
	exit_B.init(850, 400, 100, 50, exit);
}

Help::~Help()
{
	SDL_DestroyTexture(helpBack);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(menuo);
	SDL_DestroyTexture(exit);
	SDL_DestroyTexture(exito);

	helpBack =	NULL;
	menu =		NULL;
	menuo =		NULL;
	exit =		NULL;
	exito =		NULL;
}

void Help::logic()
{

}

void Help::render()
{
	apply_surface(helpBack, NULL);
	menu_B.show();
	exit_B.show();
}

void Help::handle_event()
{
	int x = 0, y = 0;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) set_next_state(STATE_EXIT);									//window X'd out

		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)											//escape key pressed
			{
				set_next_state(STATE_MENU);
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;


				if ((x > menu_B.box.x)															//Menu Button
					&& (x < menu_B.box.x + menu_B.box.w)
					&& (y > menu_B.box.y)
					&& (y < menu_B.box.y + menu_B.box.h))	menu_B.sprite = menuo;

				else if ((x > exit_B.box.x)														//Exit Button
					&& (x < exit_B.box.x + exit_B.box.w)
					&& (y > exit_B.box.y)
					&& (y < exit_B.box.y + exit_B.box.h))	exit_B.sprite = exito;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				x = event.button.x;
				y = event.button.y;

				if ((x > menu_B.box.x)
					&& (x < menu_B.box.x + menu_B.box.w)
					&& (y > menu_B.box.y)
					&& (y < menu_B.box.y + menu_B.box.h))	set_next_state(STATE_MENU);

				else if ((x > exit_B.box.x)
					&& (x < exit_B.box.x + exit_B.box.w)
					&& (y > exit_B.box.y)
					&& (y < exit_B.box.y + exit_B.box.h))	set_next_state(STATE_EXIT);

				else
				{
					menu_B.sprite = menu;
					exit_B.sprite = exit;
				}
			}
		}
	}
}
#endif