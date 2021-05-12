#pragma once

#ifndef BATS_OBJECT_H
#define BATS_OBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

class BatsObject : public BaseObject
{
public:
	BatsObject();
	~BatsObject();

	void set_x_val(const float& xVal)
	{
		x_val = xVal;
	}
	void set_y_val(const float& yVal)
	{
		y_val = yVal;
	}
	void set_x_pos(const float& xp)
	{
		x_pos = xp;
	}
	void set_y_pos(const float& yp)
	{
		y_pos = yp;
	}
	float get_x_pos() const
	{
		return x_pos;
	}
	float get_y_pos() const
	{
		return y_pos;
	}

	void set_clips();
	bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	int get_width_frame() const
	{
		return width_frame;
	}
	int get_height_frame() const
	{
		return height_frame;
	}

	std::vector <Bullet*> get_bullet_list() const
	{
		return bullet_list;
	}

	void set_bullet_list(std::vector <Bullet*>& bl_list)
	{
		bullet_list = bl_list;
	}

	SDL_Rect Get_Rect_Frame();

	void InitBullet(Bullet* p_bullet, SDL_Renderer* renderer);
	void MakeBullet1(SDL_Renderer* renderer, const int& x_limit, const int& y_limit, int& hp_x, int& hp_w, double& gunx, double& gunw, bool apod);
	void MakeBullet2(SDL_Renderer* renderer, const int& x_limit, const int& y_limit, int& hp_x, int& hp_w);
	void RemoveBullet(const int& id);

	void LoadBatsDyingSound();


private:
	float x_pos;
	float y_pos;
	float x_val;
	float y_val;
	SDL_Rect frame_clips[4];
	int frame_;
	int width_frame;
	int height_frame;
	std::vector <Bullet*> bullet_list;
};

#endif
