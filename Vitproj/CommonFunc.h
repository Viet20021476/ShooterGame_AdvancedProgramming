#pragma once

#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_renderer = NULL;
static SDL_Event g_event;

//SCREEN
const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 809;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;




struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
};

namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	bool CheckdetailedCollision(const SDL_Rect& object1, const SDL_Rect& object2, std::string s);
	void MouseMotionSound1();
	void MouseMotionSound2();
	void showSDL(SDL_Renderer* renderer);
	void showHelp(SDL_Renderer* renderer);
	int ChooseLevel(SDL_Renderer* renderer);
	int showMenu(SDL_Renderer* renderer, int& remaindertime_menu);
	int showWin(SDL_Renderer* renderer, int score, int& remaindertime_gamewin);
	int showEnd(SDL_Renderer* renderer, int score, int& remaindertime_gameover);
}


#endif