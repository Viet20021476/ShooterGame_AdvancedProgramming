#pragma once

#ifndef MONSTERS_OBJECT_H_
#define MONSTERS_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class MonstersObject : public BaseObject
{
public:
	MonstersObject();
	~MonstersObject();

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

	SDL_Rect Get_Rect_Frame();

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

	void LoadMonsDyingSound();

private:
	float x_pos;
	float y_pos;
	float x_val;
	float y_val;
	SDL_Rect frame_clips[5];
	int frame_;
	int width_frame;
	int height_frame;
};

#endif
