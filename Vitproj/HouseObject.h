#pragma once
#ifndef HOUSE_OBJECT_H
#define HOUSE_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

class HouseObject : public BaseObject
{
public:
	HouseObject();
	~HouseObject();

	bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des,std::string s);

	float get_x_pos() const
	{
		return x_pos;
	}
	float get_y_pos() const
	{
		return y_pos;
	}

	int get_width_frame() const
	{
		return width_frame;
	}
	int get_height_frame() const
	{
		return height_frame;
	}

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
