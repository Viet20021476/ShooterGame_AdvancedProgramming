#pragma once

#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Bullet.h"

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum Move_type
	{
		MOVE_UP = 0,
	    MOVE_DOWN = 1,
	    MOVE_LEFT = 2,
	    MOVE_RIGHT = 3
	};


	bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInput(SDL_Event events, SDL_Renderer* screen);
	void set_clips();
	void set_comeback_time(const int& cb_time)
	{
		come_back_time = cb_time;
	}

	SDL_Rect Get_Rect_Frame();

	void set_bullet_list(std::vector <Bullet*> bullet_list)
	{
		p_bullet_list = bullet_list;
	}

	std::vector <Bullet*> get_bullet_list() const
	{
		return p_bullet_list;
	}

	void set_x_pos(const int& x)
	{
		x_pos = x;
	}
	void set_y_pos(const int& y)
	{
		y_pos = y;
	}
	int CheckMap();

	void HandleBullet (SDL_Renderer* des);

	void RemoveBullet(const int& id);

private:
	std::vector <Bullet*> p_bullet_list;
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int width_frame;
	int height_frame;

	SDL_Rect frame_clip[7];
	Input input_type;
	int frame_;
	int status_;
	int come_back_time;

};


#endif
