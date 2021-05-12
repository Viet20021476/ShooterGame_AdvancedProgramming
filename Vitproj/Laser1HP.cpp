#include "Laser1HP.h"

Laser1HP::Laser1HP()
{

}

Laser1HP::~Laser1HP()
{

}

void Laser1HP::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\monhp.png", renderer);
}

void Laser1HP::ShowHPbar(SDL_Renderer* renderer, double& laser1hp_x, double& laser1hp_w)
{
	rect_.x = 950;
	rect_.y = 150;
	laser1hp_x = rect_.x + 15;
	SDL_Rect hp;
	hp.x = laser1hp_x;
	hp.y = rect_.y + 27;
	hp.w = laser1hp_w;
	hp.h = 8;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}

