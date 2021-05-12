#pragma once

#ifndef LASER_2_H
#define LASER_2_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"


class Laser2 : public BaseObject
{
public:
	Laser2();
	~Laser2();

	void InitLaser(Bullet* b_bullet, SDL_Renderer* renderer);
	void MakeBullet(SDL_Renderer* renderer);
	std::vector <Bullet*> get_bullet_list() const
	{
		return bullet_list;
	}
private:
	float x_pos;
	float y_pos;
	float width_frame;
	float height_frame;
	std::vector <Bullet*> bullet_list;
};




#endif

