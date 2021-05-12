#include "Magic1HP.h"

Magic1HP::Magic1HP()
{

}

Magic1HP::~Magic1HP()
{

}

void Magic1HP::InitHPbar(SDL_Renderer* renderer)
{
	LoadIMG("image\\monhp.png", renderer);
}

void Magic1HP::ShowHPbar(SDL_Renderer* renderer, double& magic1hp_x, double& magic1hp_w)
{
	rect_.x = 950;
	rect_.y = 0;
	magic1hp_x = rect_.x + 15;
	SDL_Rect hp;
	hp.x = magic1hp_x;
	hp.y = rect_.y + 27;
	hp.w = magic1hp_w;
	hp.h = 8;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hp);

	Render(renderer);
}