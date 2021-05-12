#pragma once

#ifndef GAME_ILLUSTRATE_H_
#define GAME_ILLUSTRATE_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"

class GameILL : public BaseObject
{
public:
	GameILL();
	~GameILL();

	void setNum(const int& num)
	{
		number = num;
	}
	void addPos(const int& x_pos);
	void Show(SDL_Renderer* renderer, MainObject p_player);
	void Initlives(SDL_Renderer* renderer, MainObject p_player);
	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer,int hp_x,int hp_w);

	void Increase();
	void Decrease();

	void Set_size_pos_list()
	{
		pos_list.resize(3);
	}

	void set_number()
	{
		number = 3;
	}

private:
	int number;
	std::vector <int> pos_list;

};






#endif

