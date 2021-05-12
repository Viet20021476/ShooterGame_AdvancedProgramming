
#include "BatHP.h"

BatHP::BatHP()
{

}

BatHP::~BatHP()
{

}

void BatHP::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\monhp.png", renderer);
}

void BatHP::ShowHPbar(SDL_Renderer* renderer, BatsObject* p_bat, int hp_x, int hp_w)
{
	rect_.x = p_bat->get_x_pos() + 15;
	rect_.y = p_bat->get_y_pos() - 20;
	SDL_Rect hp;
	hp.x = hp_x + 30;
	hp.y = rect_.y + 27;
	hp.w = hp_w;
	hp.h = 8;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}