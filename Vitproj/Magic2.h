#pragma once

#ifndef MAGIC_2_H
#define MAGIC_2_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

class Magic2 : public BaseObject
{
public:
	Magic2();
	~Magic2();

	//bool LoadIMG(std::string path, SDL_Renderer* screen);

	void InitBullet(Bullet* turr_bullet, SDL_Renderer* renderer);
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
