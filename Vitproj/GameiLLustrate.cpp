#include "GameiLLustrate.h"
#include <iostream>

GameILL::GameILL()
{
	number = 3;
}

GameILL::~GameILL()
{

}

void GameILL::addPos(const int& x_pos)
{
	pos_list.push_back(x_pos);
}

void GameILL::Initlives(SDL_Renderer* renderer, MainObject p_player)
{
	LoadIMG("image\\heart.png", renderer);
	static int count = 0;
	if (pos_list.size() != 0 || count == 0) 
	{
		addPos(p_player.GetRect().x);
		addPos(p_player.GetRect().x + 40);
		addPos(p_player.GetRect().x + 80);
		count++;
	}
	
	
	if (pos_list.size() >= 4)
	{
		pos_list.erase(pos_list.begin());
		pos_list.erase(pos_list.begin());
		pos_list.erase(pos_list.begin());
	}
}

void GameILL::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\HPbar.png", renderer);
}

void GameILL::ShowHPbar(SDL_Renderer* renderer, int hp_x, int hp_w)
{
	rect_.x = 1080;
	rect_.y = 10;
	SDL_Rect hp;
	hp.x = hp_x;
	hp.y = 23;
	hp.w = hp_w;
	hp.h = 25;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}

void GameILL::Show(SDL_Renderer* renderer, MainObject p_player)
{
	for (int i = 0; i < pos_list.size(); i++)
	{
		rect_.x = pos_list.at(i) - 15;
		rect_.y = p_player.GetRect().y - 30;
		Render(renderer);
	}
	
}

void GameILL::Decrease()
{
	number--;
	if(number >=0) pos_list.pop_back();
}

void GameILL::Increase()
{
	number++;
	int last_pos = pos_list.back();
	last_pos += 40;
	pos_list.push_back(last_pos);
}