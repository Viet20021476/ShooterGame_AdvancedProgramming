#include "HouseObject.h"

HouseObject::HouseObject()
{
	x_pos = 1000;
	y_pos = 500;
	width_frame = 0;
	height_frame = 0;
}

HouseObject::~HouseObject()
{

}

bool HouseObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadIMG(path, screen);
	if (ret == true)
	{
		width_frame = rect_.w;
		height_frame = rect_.h;
	}
	return ret;
}

void HouseObject::Show(SDL_Renderer* des, std::string s)
{
	if (s == "1") 
	{
		rect_.x = 1000;
		rect_.y = 450;
		SDL_Rect renderQuad = { rect_.x, rect_.y, 300, 400 };
		SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
	}

	else if (s == "2")
	{
		rect_.x = 830;
		rect_.y = -30;
		SDL_Rect renderQuad = { rect_.x, rect_.y, 150, 250 };
		SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
	}

	else if (s == "3")
	{
		rect_.x = 860;
		rect_.y = 70;
		SDL_Rect renderQuad = { rect_.x, rect_.y, 100, 250 };
		SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
	}

	else if (s == "4")
	{
		rect_.x = 860;
		rect_.y = 370;
		SDL_Rect renderQuad = { rect_.x, rect_.y, 100, 250 };
		SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
	}

	else if (s == "5")
	{
		rect_.x = 830;
		rect_.y = 600;
		SDL_Rect renderQuad = { rect_.x, rect_.y, 150, 250 };
		SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
	}

	else if (s == "6")
	{
		rect_.x = 1000;
		rect_.y = 100;
		SDL_Rect renderQuad = { rect_.x, rect_.y, 300, 380 };
		SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
	}

}

void HouseObject::InitBullet(Bullet* turr_bullet, SDL_Renderer* renderer)
{
	bool ret = turr_bullet->LoadIMG("image\\redbullet.png", renderer);
	turr_bullet->set_is_move(true);
	turr_bullet->set_bullet_dir(Bullet::DIR_DIAGONAL);
	turr_bullet->SetRect(860, -10);
	bullet_list.push_back(turr_bullet);
	
}


void HouseObject::MakeBullet(SDL_Renderer* renderer)
{
	
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* p_bullet = bullet_list.at(i);
		if (p_bullet->get_is_move())
		{
			p_bullet->HandleMove(0, 0);
			p_bullet->Render(renderer);
		}
		else
		{
			if ((int)(SDL_GetTicks() / 1000) % 2 == 0) 
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(860, -10);
			}
			else
			{
				p_bullet->SetRect(860, -10);
				p_bullet->set_is_move(false);
			}
			
		}
	}
	
}


