#include "Magic2HP.h"

Magic2HP::Magic2HP()
{

}

Magic2HP::~Magic2HP()
{

}

void Magic2HP::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\monhp.png", renderer);
}

void Magic2HP::ShowHPbar(SDL_Renderer* renderer, double& magic2hp_x, double& magic2hp_w)
{
	rect_.x = 950;
	rect_.y = 600;
	magic2hp_x = rect_.x + 15;
	SDL_Rect hp;
	hp.x = magic2hp_x;
	hp.y = rect_.y + 27;
	hp.w = magic2hp_w;
	hp.h = 8;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}