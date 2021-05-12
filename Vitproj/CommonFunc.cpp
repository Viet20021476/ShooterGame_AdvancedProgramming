#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
	//object 1 - threats, object 2 - bullets
		if (object1.h <= 80)
		{
			if (object1.x < object2.x && object2.x < (object1.x + object1.w) - 60 && object1.y < object2.y && object2.y < (object1.y + object1.h) + 20)
				return true;

			if (object2.x < object1.x && object1.x < (object2.x + object2.w) - 60 && object1.y < object2.y && object2.y < (object1.y + object1.h) + 50)
				return true;
		}

		else
		{
			if (object1.x < object2.x && object2.x < (object1.x + object1.w) - 60 && object1.y < object2.y && object2.y < (object1.y + object1.h) - 20)
				return true;

			if (object2.x < object1.x && object1.x < (object2.x + object2.w) - 60 && object1.y < object2.y && object2.y < (object1.y + object1.h))
				return true;
		}
	
	return false;
}

bool SDLCommonFunc::CheckdetailedCollision(const SDL_Rect& object1, const SDL_Rect& object2, std::string s)
{
	if (s == "case 1")
	{
		if (object1.x < object2.x && object1.x + object1.w - 30 > object2.x + object2.w && object1.y < object2.y && object1.y + object1.h > object2.y + object2.h - 30)
			return true;
	}
	// object 1 - player, object 2 - bats

	else if (s == "case 2")
	{
		if (object2.x + object2.w - 50 > object1.x && object1.y < object2.y && object2.x + object2.w < object1.x + object1.w && object2.y + object2.h < object1.y + object1.h)
				return true;
		
	}

	else if (s == "case 3")
	{
		if ((object1.x + 80 < object2.x + object2.w && object2.x + object2.w < object1.x + object1.w && object2.y < object1.y + object1.h && object1.y + object1.h < object2.y + object2.h) || (object1.x < object2.x - 62 && object2.x < object1.x + object1.w && object2.y < object1.y + object1.h && object1.y + object1.h < object2.y + object2.h))
			return true;
	}
	return false;
}

void SDLCommonFunc::MouseMotionSound1()
{
	Mix_Chunk* soundEffect = Mix_LoadWAV("sound\\mou.wav");
	Mix_PlayChannel(-1, soundEffect, 0);
}

void SDLCommonFunc::MouseMotionSound2()
{
	Mix_Chunk* soundEffect = Mix_LoadWAV("sound\\mouse_motion.wav");
	Mix_PlayChannel(-1, soundEffect, 0);
}

void SDLCommonFunc::showSDL(SDL_Renderer* renderer)
{
	BaseObject SDL_bg;
	SDL_bg.LoadIMG("image\\SDL_bg.png", renderer);

	SDL_bg.Render(renderer, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);
}

void SDLCommonFunc::showHelp(SDL_Renderer* renderer)
{
	BaseObject SDL_help;
	SDL_help.LoadIMG("image\\help1.png", renderer);

	SDL_help.RenderHelp(renderer, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);
}

int SDLCommonFunc::ChooseLevel(SDL_Renderer* renderer)
{
	BaseObject menu_bg;
	menu_bg.LoadIMG("image\\menu_bg.jpg", renderer);
	SDL_Color color[3] = { {255,255,255},{255,0,0},{102,0,102} };
	TTF_Font* font = TTF_OpenFont("font\\39335_UniversCondensed.ttf", 50);

	bool level_running = true;
	const int menuItem = 4;
	SDL_Surface* menus[menuItem];

	menus[0] = TTF_RenderText_Solid(font, "Easy", color[0]);
	menus[1] = TTF_RenderText_Solid(font, "Medium", color[0]);
	menus[2] = TTF_RenderText_Solid(font, "Hard", color[0]);
	menus[3] = TTF_RenderText_Solid(font, "Super Hard", color[0]);


	while (level_running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				menu_bg.Free();
				SDL_FreeSurface(menus[0]);
				SDL_FreeSurface(menus[1]);
				SDL_FreeSurface(menus[2]);
				SDL_FreeSurface(menus[3]);
				level_running = false;
			}

			if (event.type == SDL_MOUSEMOTION)
			{
				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 300 && event.button.y <= 350)
				{
					MouseMotionSound2();
					menus[0] = TTF_RenderText_Solid(font, "Easy", color[1]);
				}
				else menus[0] = TTF_RenderText_Solid(font, "Easy", color[0]);

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 400 && event.button.y <= 450)
				{
					MouseMotionSound2();
					menus[1] = TTF_RenderText_Solid(font, "Medium", color[1]);
				}
				else menus[1] = TTF_RenderText_Solid(font, "Medium", color[0]);

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 500 && event.button.y <= 550)
				{
					MouseMotionSound2();
					menus[2] = TTF_RenderText_Solid(font, "Hard", color[1]);
				}
				else menus[2] = TTF_RenderText_Solid(font, "Hard", color[0]);

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 600 && event.button.y <= 650)
				{
					MouseMotionSound2();
					menus[3] = TTF_RenderText_Solid(font, "Super Hard", color[1]);
				}
				else menus[3] = TTF_RenderText_Solid(font, "Super Hard", color[0]);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 300 && event.button.y <= 350)
				{
					return 1;
				}

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 400 && event.button.y <= 450)
				{
					return 2;
				}
				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 500 && event.button.y <= 550)
				{
					return 3;
				}

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 600 && event.button.y <= 650)
				{
					return 4;
				}
			}
		}
		menu_bg.Render(renderer, NULL);
		SDL_Texture* easyMessage = SDL_CreateTextureFromSurface(renderer, menus[0]);
		SDL_Texture* mediumMessage = SDL_CreateTextureFromSurface(renderer, menus[1]);
		SDL_Texture* hardMessage = SDL_CreateTextureFromSurface(renderer, menus[2]);
		SDL_Texture* superhardMessage = SDL_CreateTextureFromSurface(renderer, menus[3]);

		SDL_Rect easyRect, mediumRect, hardRect, superhardRect;
		easyRect.w = mediumRect.w = hardRect.w = superhardRect.w =  150;
		easyRect.h = mediumRect.h = hardRect.h = superhardRect.h = 50;
		easyRect.x = mediumRect.x = hardRect.x = superhardRect.x = 550;
		easyRect.y = 300;
		mediumRect.y = 400;
		hardRect.y = 500;
		superhardRect.y = 600;
		
		SDL_RenderCopy(renderer, easyMessage, NULL, &easyRect);
		SDL_RenderCopy(renderer, mediumMessage, NULL, &mediumRect);
		SDL_RenderCopy(renderer, hardMessage, NULL, &hardRect);
		SDL_RenderCopy(renderer, superhardMessage, NULL, &superhardRect);
		SDL_RenderPresent(renderer);
	}
}



int SDLCommonFunc::showMenu(SDL_Renderer* renderer, int& remaindertime_menu)
{
	BaseObject menu_bg;
	menu_bg.LoadIMG("image\\menu_bg.jpg", renderer);
	SDL_Color color[3] = { {255,255,255},{255,0,0},{102,0,102} };
	TTF_Font* font = TTF_OpenFont("font\\39335_UniversCondensed.ttf", 50);
	
	bool menu_running = true;
	const int menuItem = 3;
	SDL_Surface* menus[menuItem];
	SDL_Surface* name = TTF_RenderText_Solid(font, "SHOOTER GAME", color[2]);
	
	SDL_Rect pos_a[menuItem];

	pos_a[0].x = 550;
	pos_a[0].y = 300;
	pos_a[1].x = 550;
	pos_a[1].y = 500;

	while (menu_running)
	{
		SDL_Event event;
		remaindertime_menu = SDL_GetTicks() / 1000;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				menu_bg.Free();
				SDL_FreeSurface(menus[0]);
				SDL_FreeSurface(menus[1]);
				menu_running = false;
				return -1;
			}

			if (event.type == SDL_MOUSEMOTION)
			{
				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 300 && event.button.y <= 350)
				{
					MouseMotionSound2();
					menus[0] = TTF_RenderText_Solid(font, "Play", color[1]);
				}
				else menus[0] = TTF_RenderText_Solid(font, "Play", color[0]);

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 400 && event.button.y <= 450)
				{
					MouseMotionSound2();
					menus[1] = TTF_RenderText_Solid(font, "Help", color[1]);
				}
				else menus[1] = TTF_RenderText_Solid(font, "Help", color[0]);

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 500 && event.button.y <= 550)
				{
					MouseMotionSound2();
					menus[2] = TTF_RenderText_Solid(font, "Exit", color[1]);
				}
				else menus[2] = TTF_RenderText_Solid(font, "Exit", color[0]);
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 300 && event.button.y <= 350) 
				{
					menu_running = false;
					return 2;
				}

				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 400 && event.button.y <= 450)
				{
					showHelp(renderer);
				}
				if (event.button.x >= 550 && event.button.x <= 700 && event.button.y >= 500 && event.button.y <= 550)
				{
					menu_running = false;
					return -1;
				}
			}
		}
		menu_bg.Render(renderer, NULL);
		SDL_Texture* playMessage = SDL_CreateTextureFromSurface(renderer, menus[0]);
		SDL_Texture* helpMessage = SDL_CreateTextureFromSurface(renderer, menus[1]);
		SDL_Texture* exitMessage = SDL_CreateTextureFromSurface(renderer, menus[2]);
		SDL_Texture* nameMessage = SDL_CreateTextureFromSurface(renderer, name);

		SDL_Rect playRect,helpRect, exitRect,nameRect;
		playRect.w = exitRect.w = 150;
		playRect.h = exitRect.h = 50;
		playRect.x = pos_a[0].x;
		playRect.y = pos_a[0].y;

		helpRect.x = 550;
		helpRect.y = 400;
		helpRect.w = 150;
		helpRect.h = 50;

		exitRect.x = pos_a[1].x;
		exitRect.y = pos_a[1].y;

		nameRect.x = 250;
		nameRect.y = 15;
		nameRect.w = 800;
		nameRect.h = 300;
	
		SDL_RenderCopy(renderer, playMessage, NULL, &playRect);
		SDL_RenderCopy(renderer, helpMessage, NULL, &helpRect);
		SDL_RenderCopy(renderer, exitMessage, NULL, &exitRect);
		SDL_RenderCopy(renderer, nameMessage, NULL, &nameRect);
		SDL_RenderPresent(renderer);
	}
}

int SDLCommonFunc::showWin(SDL_Renderer* renderer, int score, int& remaindertime_gamewin)
{
	BaseObject menu_bg;
	menu_bg.LoadIMG("image\\dark_bg.jpg", renderer);
	SDL_Color color[3] = { {255,255,255},{255,0,0}, {100,100,100} };
	TTF_Font* font = TTF_OpenFont("font\\39335_UniversCondensed.ttf", 50);
	bool win_running = true;
	const int menuItem = 2;

	SDL_Surface* menus[menuItem];
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "You Win", color[2]);
	SDL_Surface* SCORE = TTF_RenderText_Solid(font, (("Your score: ") + std::to_string(score)).c_str(), color[2]);
	menus[0] = TTF_RenderText_Solid(font, "Play Again", color[0]);
	menus[1] = TTF_RenderText_Solid(font, "Exit", color[0]);
	SDL_Event event;

	while (win_running)
	{
		remaindertime_gamewin = SDL_GetTicks() / 1000 - 2;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				win_running = false;
				return 1;
			}

			if (event.type == SDL_MOUSEMOTION)
			{
				if (event.button.x >= 500 && event.button.x <= 650 && event.button.y >= 600 && event.button.y <= 650)
				{
					MouseMotionSound2();
					menus[0] = TTF_RenderText_Solid(font, "Play Again", color[1]);
				}
				else menus[0] = TTF_RenderText_Solid(font, "Play Again", color[0]);

				if (event.button.x >= 500 && event.button.x <= 575 && event.button.y >= 650 && event.button.y <= 700)
				{
					MouseMotionSound2();
					menus[1] = TTF_RenderText_Solid(font, "Exit", color[1]);
				}
				else menus[1] = TTF_RenderText_Solid(font, "Exit", color[0]);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.x >= 500 && event.button.x <= 650 && event.button.y >= 600 && event.button.y <= 650)
				{
					win_running = false;
					return 0;
				}
				else if (event.button.x >= 500 && event.button.x <= 575 && event.button.y >= 650 && event.button.y <= 700)
				{
					win_running = false;
					return 2;
				}
			}
		}

		menu_bg.Render(renderer, NULL);
		SDL_Texture* playagainMessage = SDL_CreateTextureFromSurface(renderer, menus[0]);
		SDL_Texture* exitMessage = SDL_CreateTextureFromSurface(renderer, menus[1]);
		SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
		SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, SCORE);

		SDL_Rect playagainRect, exitRect, gameoverRect, scoreRect;
		playagainRect.w = 150;
		playagainRect.h = exitRect.h = 50;
		exitRect.w = 75;
		playagainRect.x = 500;
		playagainRect.y = 600;
		exitRect.x = 500;
		exitRect.y = 650;
		gameoverRect.x = 350;
		gameoverRect.y = 150;
		gameoverRect.w = 500;
		gameoverRect.h = 200;
		scoreRect.x = 470;
		scoreRect.y = 320;
		scoreRect.w = 250;
		scoreRect.h = 100;


		SDL_RenderCopy(renderer, playagainMessage, NULL, &playagainRect);
		SDL_RenderCopy(renderer, exitMessage, NULL, &exitRect);
		SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
		SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

		SDL_RenderPresent(renderer);
	}
}

int SDLCommonFunc::showEnd(SDL_Renderer* renderer, int score, int& remaindertime_gameover)
{
	BaseObject menu_bg;
	menu_bg.LoadIMG("image\\dark_bg.jpg", renderer);
	SDL_Color color[3] = { {255,255,255},{255,0,0}, {100,100,100} };
	TTF_Font* font = TTF_OpenFont("font\\39335_UniversCondensed.ttf", 50);
	bool end_running = true;
	const int menuItem = 2;

	SDL_Surface* menus[menuItem];
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", color[2]);
	SDL_Surface* SCORE = TTF_RenderText_Solid(font, (("Your score: ") + std::to_string(score)).c_str(), color[2]);
	menus[0] = TTF_RenderText_Solid(font, "Play Again", color[0]);
	menus[1] = TTF_RenderText_Solid(font, "Exit", color[0]);
	SDL_Event event;

	while (end_running)
	{
		remaindertime_gameover = SDL_GetTicks() / 1000 - 2;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				end_running = false;
				return 1;
			}

            if (event.type == SDL_MOUSEMOTION)
			{
				if (event.button.x >= 500 && event.button.x <= 650 && event.button.y >= 600 && event.button.y <= 650)
			    {
					MouseMotionSound2();
				    menus[0] = TTF_RenderText_Solid(font, "Play Again", color[1]);
				}
				else menus[0] = TTF_RenderText_Solid(font, "Play Again", color[0]);

				if (event.button.x >= 500 && event.button.x <= 575 && event.button.y >= 650 && event.button.y <= 700)
				{
					MouseMotionSound2();
					menus[1] = TTF_RenderText_Solid(font, "Exit", color[1]);
				}
				else menus[1] = TTF_RenderText_Solid(font, "Exit", color[0]);
			}

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.x >= 500 && event.button.x <= 650 && event.button.y >= 600 && event.button.y <= 650) 
				{
					end_running = false;
					return 0;
				}
				else if (event.button.x >= 500 && event.button.x <= 575 && event.button.y >= 650 && event.button.y <= 700)
				{
					end_running = false;
					return 1;
				}
			}
		}

		menu_bg.Render(renderer, NULL);
		SDL_Texture* playagainMessage = SDL_CreateTextureFromSurface(renderer, menus[0]);
		SDL_Texture* exitMessage = SDL_CreateTextureFromSurface(renderer, menus[1]);
		SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
		SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, SCORE);

		SDL_Rect playagainRect, exitRect, gameoverRect, scoreRect;
		playagainRect.w = 150;
		playagainRect.h = exitRect.h = 50;
		exitRect.w = 75;
		playagainRect.x = 500;
		playagainRect.y = 600;
		exitRect.x = 500;
		exitRect.y = 650;
		gameoverRect.x = 350;
		gameoverRect.y = 150;
		gameoverRect.w = 500;
		gameoverRect.h = 200;
		scoreRect.x = 470;
		scoreRect.y = 320;
		scoreRect.w = 250;
		scoreRect.h = 100;


		SDL_RenderCopy(renderer, playagainMessage, NULL, &playagainRect);
		SDL_RenderCopy(renderer, exitMessage, NULL, &exitRect);
		SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
		SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

		SDL_RenderPresent(renderer);
	}
}








