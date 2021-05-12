
#include "Bullet.h"

Bullet::Bullet()
{
	x_val = 0;
	y_val = 0;
	is_move = false;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMove(const int& x_border, const int& y_border)
{
	if (bullet_dir == DIR_UP)
	{
		rect_.y -= x_val;
		if (rect_.x > x_border)
		{
			is_move = false;
		}
	}

	if (bullet_dir == DIR_DOWN)
	{
		rect_.y += x_val;
		if (rect_.x > x_border)
		{
			is_move = false;
		}
	}

	if (bullet_dir == DIR_RIGHT)
	{
		rect_.x += x_val;
		if (rect_.x > x_border)
		{
			is_move = false;
		}
	}
	if (bullet_dir == DIR_LEFT)
	{
		rect_.x -= x_val;
		if (rect_.x < 0)
		{
			is_move = false;
		}
	}

	if (bullet_dir == DIR_DIAGONAL)
	{
		if (rect_.x >= 500) 
		{
			rect_.x -= 12;
			rect_.y += 4;
		}
		if (rect_.x < 500)
		{
			rect_.x -= 12;
			rect_.y += 0;
		}
		if (rect_.x < 0)
		{
			is_move = false;
		}

	}
}

void Bullet::LoadShootingSound()
{
	Mix_Chunk* soundEffect = Mix_LoadWAV("sound\\gun_sound.wav");
	Mix_PlayChannel(-1, soundEffect, 0);
}

void Bullet::LoadTurretShootingSound()
{
	Mix_Chunk* soundEffect = Mix_LoadWAV("sound\\turr_sound.wav");
	Mix_PlayChannel(-1, soundEffect, 0);
}