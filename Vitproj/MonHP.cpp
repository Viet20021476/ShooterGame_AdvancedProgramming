
#include "MonHP.h"
#include <iostream>

MonHP::MonHP()
{
	
}

MonHP::~MonHP()
{

}

void MonHP::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\monhp.png", renderer);
}

void MonHP::ShowHPbar(SDL_Renderer* renderer,MonstersObject* p_monster,int hp_x,int hp_w)
{
	
	rect_.x = p_monster->get_x_pos();
	rect_.y = p_monster->get_y_pos() - 29;
	//hp_x = rect_.x + 15;
	SDL_Rect hp;
	hp.x = hp_x + 17;
	hp.y = rect_.y + 27;
	hp.w = hp_w + 3;
	hp.h = 8;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}