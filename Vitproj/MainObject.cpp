
#include "MainObject.h"

MainObject::MainObject()
{
	frame_ = 0;
	x_pos = 800;
	y_pos = 400;
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status_ = -1;
}

MainObject :: ~MainObject()
{

}

bool MainObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
	int ret = BaseObject::LoadIMG(path, screen);
	if (ret == true)
	{
		width_frame = rect_.w / 5.9;
		height_frame = rect_.h;
	}
	return ret;
}

SDL_Rect MainObject::Get_Rect_Frame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame;
	rect.h = height_frame;

	return rect;
}

void MainObject::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 6; i++)
		{
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	switch (status_)
	{
	case MOVE_UP:
		LoadIMG("image\\sp_up.png", des);
		break;

	case MOVE_DOWN:
		LoadIMG("image\\sp_down.png", des);
		break;

	case MOVE_LEFT:
		LoadIMG("image\\sp_left.png", des);
		break;

	case MOVE_RIGHT:
		LoadIMG("image\\sp_right.png", des);
		break;
	}

	if (input_type.up_ == 1 || input_type.down_ == 1 || input_type.left_ == 1 || input_type.right_ == 1)
		frame_++;
	
	if (frame_ >= 4)
		frame_ = 0;

	rect_.x = x_pos;
	rect_.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame, height_frame };
	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

int MainObject::CheckMap() 
{
	if (x_pos >= SCREEN_WIDTH - 50) return 1;
    if (x_pos <= -10) return 2;
    if (y_pos >= SCREEN_HEIGHT - 90 ) return 3;
	if (y_pos <= 0) return 4;
	return 0;
}

void MainObject::HandleInput(SDL_Event events, SDL_Renderer* screen)
{
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	
	if (keyState[SDL_SCANCODE_UP])
	{
		status_ = MOVE_UP;
		input_type.up_ = 1;
		if (CheckMap() != 4) y_pos -= 20;
	}

	else if (keyState[SDL_SCANCODE_DOWN])
	{
		status_ = MOVE_DOWN;
		input_type.down_ = 1;
		if (CheckMap() != 3) y_pos += 20;
	}

	else if (keyState[SDL_SCANCODE_LEFT])
	{
		status_ = MOVE_LEFT;
		input_type.left_ = 1;
		if (CheckMap() != 2) x_pos -= 20;
	}

	else if (keyState[SDL_SCANCODE_RIGHT])
	{
		status_ = MOVE_RIGHT;
		input_type.right_ = 1;
		if (CheckMap() != 1) x_pos += 20;
	}

	else 
		frame_ = 0;

	if (keyState[SDL_SCANCODE_SPACE])
	{
		Bullet* p_bullet = new Bullet();

		if (status_ == MOVE_UP)
		{
			p_bullet->LoadIMG("image\\bullet_vertical.png", screen);
			p_bullet->set_bullet_dir(Bullet::DIR_UP);
			p_bullet->SetRect(rect_.x, rect_.y + 20);
			p_bullet->LoadShootingSound();
		}

		if (status_ == MOVE_DOWN)
		{
			p_bullet->LoadIMG("image\\bullet_vertical.png", screen);
			p_bullet->set_bullet_dir(Bullet::DIR_DOWN);
			p_bullet->SetRect(rect_.x, rect_.y + 18);
			p_bullet->LoadShootingSound();
		}

		if (status_ == MOVE_LEFT)
		{
			p_bullet->LoadIMG("image\\bullet_horizontal.png", screen);
			p_bullet->set_bullet_dir(Bullet::DIR_LEFT);
			p_bullet->SetRect(rect_.x - width_frame + 40, rect_.y + height_frame * 0.25);
			p_bullet->LoadShootingSound();
		}

		if (status_ == MOVE_RIGHT)
		{
			p_bullet->LoadIMG("image\\bullet_horizontal.png", screen);
			p_bullet->set_bullet_dir(Bullet::DIR_RIGHT);
			p_bullet->SetRect(rect_.x + width_frame - 20, rect_.y + height_frame * 0.25);
			p_bullet->LoadShootingSound();
		}

		p_bullet->set_x_val(30);
		p_bullet->set_is_move(true);

		p_bullet_list.push_back(p_bullet);
	}
	
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		Bullet* p_bullet = p_bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}

void MainObject::RemoveBullet(const int& id)
{
	int size = p_bullet_list.size();
	if (size > 0 && id < size)
	{
		Bullet* bullet = p_bullet_list.at(id);
		p_bullet_list.erase(p_bullet_list.begin() + id);

		if (bullet)
		{
			delete bullet;
			bullet = NULL;
		}
	}
}