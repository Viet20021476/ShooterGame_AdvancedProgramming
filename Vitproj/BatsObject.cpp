
#include "BatsObject.h"


BatsObject::BatsObject()
{
	width_frame = 0;
	height_frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	frame_ = 0;
}

BatsObject::~BatsObject()
{

}

bool BatsObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadIMG(path, screen);
	if (ret == true)
	{
		width_frame = rect_.w / 4;
		height_frame = rect_.h;
	}
	return ret;
}

SDL_Rect BatsObject::Get_Rect_Frame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame;
	rect.h = height_frame;

	return rect;
}

void BatsObject::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 4; i++)
		{
			frame_clips[i].x = i * width_frame;
			frame_clips[i].y = 0;
			frame_clips[i].w = width_frame;
			frame_clips[i].h = height_frame;
		}
	}
}

void BatsObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	frame_ = (SDL_GetTicks() / 100) % 3;
	x_pos += 1;

	if (frame_ >= 4)
		frame_ = 0;

	SDL_Rect* currentClip = &frame_clips[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, 110, 110 };
	SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
}

void BatsObject::InitBullet(Bullet* p_bullet, SDL_Renderer* renderer)
{
	if (p_bullet != NULL)
	{
	    bool ret = p_bullet->LoadIMG("image\\bat_bullet.png", renderer);
		p_bullet->set_is_move(true);
		p_bullet->set_bullet_dir(Bullet::DIR_RIGHT);
		p_bullet->SetRect(x_pos + 20, y_pos - 10);
		p_bullet->set_x_val(15);
		bullet_list.push_back(p_bullet);
	}
}

void BatsObject::MakeBullet1(SDL_Renderer* renderer, const int& x_limit, const int& y_limit, int& hp_x, int& hp_w, double& gunx, double& gunw, bool apod)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* p_bullet = bullet_list.at(i);
		if (apod == true) 
		{
			if (p_bullet->get_is_move())
			{
				if (p_bullet->GetRect().y > 290 && p_bullet->GetRect().y < 400)
				{
					if (p_bullet->GetRect().x > 950 && hp_w > 0)
					{
						hp_x++;
						hp_w--;
					}
					p_bullet->HandleMove(x_limit - 200, y_limit);
				}

				else
				{
					if (p_bullet->GetRect().x > 800 && gunw > 0)
					{
						gunx += 0.5;
						gunw -= 0.5;

					}
					p_bullet->HandleMove(x_limit - 350, y_limit);
				}
				p_bullet->Render(renderer);
			}

			else
			{
				if ((int)(SDL_GetTicks() / 1000) % 3 == 0)
				{
					p_bullet->set_is_move(true);
					p_bullet->SetRect(x_pos + 20, y_pos - 10);
				}

				else
				{
					p_bullet->set_is_move(false);
				}

			}
		}

		else if(apod == false)
		{
			if (p_bullet->get_is_move())
			{
				if (p_bullet->GetRect().x > 950 && hp_w > 0)
				{
					hp_x++;
					hp_w--;
				}
				p_bullet->HandleMove(x_limit - 200, y_limit);
			}

			else
			{
				if ((int)(SDL_GetTicks() / 1000) % 3 == 0)
				{
					p_bullet->set_is_move(true);
					p_bullet->SetRect(x_pos + 20, y_pos - 10);
				}

				else
				{
					p_bullet->set_is_move(false);
				}
			}
			p_bullet->Render(renderer);
		}	
	}	
}


void BatsObject::MakeBullet2(SDL_Renderer* renderer, const int& x_limit, const int& y_limit, int& hp_x, int& hp_w)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		Bullet* p_bullet = bullet_list.at(i);

		if (p_bullet->get_is_move())
		{
			if (p_bullet->GetRect().y > 290 && p_bullet->GetRect().y < 400)
			{
				if (p_bullet->GetRect().x > 950 && hp_w > 0)
				{
					hp_x++;
					hp_w--;
				}
				p_bullet->HandleMove(x_limit - 200, y_limit);
			}

			else
			{
				if (p_bullet->GetRect().x > 830 && hp_w > 0)
				{
					hp_x++;
					hp_w--;

				}
				p_bullet->HandleMove(x_limit - 350, y_limit);
			}
			p_bullet->Render(renderer);
		}

		else
		{
			if ((int)(SDL_GetTicks() / 1000) % 3 == 0)
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(x_pos + 20, y_pos - 10);
			}

			else
			{
				p_bullet->set_is_move(false);
			}

		}

	}
}

void BatsObject::RemoveBullet(const int& id)
{
	int size = bullet_list.size();
	if (size > 0 && id < size)
	{
		Bullet* bullet = bullet_list.at(id);
		bullet_list.erase(bullet_list.begin() + id);

		if (bullet)
		{
			delete bullet;
			bullet = NULL;
		}
	}
}

void BatsObject::LoadBatsDyingSound()
{
	Mix_Chunk* soundEffect = Mix_LoadWAV("sound\\bats_dying.wav");
	Mix_PlayChannel(-1, soundEffect, 0);
}