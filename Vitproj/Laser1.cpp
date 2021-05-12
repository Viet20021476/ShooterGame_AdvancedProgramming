#include "Laser1.h"

Laser1::Laser1()
{

}

Laser1::~Laser1()
{

}

void Laser1::InitLaser(Bullet* b_bullet,SDL_Renderer* renderer)
{
	bool ret = b_bullet->LoadIMG("image\\bluebullet.png", renderer);
	b_bullet->set_is_move(true);
	b_bullet->set_bullet_dir(Bullet::DIR_DIAGONAL);
	b_bullet->SetRect(860, 100);
	bullet_list.push_back(b_bullet);

}

void Laser1::MakeBullet(SDL_Renderer* renderer)
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
				p_bullet->SetRect(860, 100);
			}
			else
			{
				p_bullet->SetRect(860, 100);
				p_bullet->set_is_move(false);
			}
		}
	}
}