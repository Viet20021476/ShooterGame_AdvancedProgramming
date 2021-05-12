#include "Magic2.h"

Magic2::Magic2()
{

}

void Magic2::InitBullet(Bullet* turr_bullet, SDL_Renderer* renderer)
{
	bool ret = turr_bullet->LoadIMG("image\\redbullet.png", renderer);
	turr_bullet->set_is_move(true);
	turr_bullet->set_bullet_dir(Bullet::DIR_DIAGONAL);
	turr_bullet->SetRect(860, 610);
	bullet_list.push_back(turr_bullet);

}


void Magic2::MakeBullet(SDL_Renderer* renderer)
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
				p_bullet->SetRect(860, 610);
			}
			else
			{
				p_bullet->SetRect(860, 610);
				p_bullet->set_is_move(false);
			}
		}
	}

}
