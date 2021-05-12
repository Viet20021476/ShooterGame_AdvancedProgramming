#include "Laser2HP.h"

Laser2HP::Laser2HP()
{

}

Laser2HP::~Laser2HP()
{

}

void Laser2HP::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\monhp.png", renderer);
}

void Laser2HP::ShowHPbar(SDL_Renderer* renderer, double& laser2hp_x, double& laser2hp_w)
{
	rect_.x = 860;
	rect_.y = 330;
	laser2hp_x = rect_.x + 15;
	SDL_Rect hp;
	hp.x = laser2hp_x;
	hp.y = rect_.y + 27;
	hp.w = laser2hp_w;
	hp.h = 8;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}

