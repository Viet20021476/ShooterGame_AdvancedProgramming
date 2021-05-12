#pragma once

#ifndef BULLET_H_
#define BULLETT_H_

#include "BaseObject.h"
#include "CommonFunc.h"

class Bullet : public BaseObject
{
public:
	Bullet();
	~Bullet();

	enum BULLET_DIR
	{
		DIR_UP = 18,
		DIR_DOWN = 19,
		DIR_LEFT = 20,
		DIR_RIGHT = 21,
		DIR_DIAGONAL = 22,
	};

	void set_x_val(const int& xVal)
	{
		x_val = xVal;
	}
	void set_y_val(const int& yVal)
	{
		y_val = yVal;
	}

	int get_x_val() const
	{
		return x_val;
	}
	int get_y_val() const
	{
		return y_val;
	}

	void set_is_move(const bool& ismove)
	{
		is_move = ismove;
	}
	bool get_is_move() const
	{
		return is_move;
	}

	void set_bullet_dir(const unsigned int& bulletDir)
	{
		bullet_dir = bulletDir;
	}
	int get_bullet_dir()
	{
		return bullet_dir;
	}

	void HandleMove(const int& x_border, const int& y_border);
	void LoadShootingSound();
	void LoadTurretShootingSound();
	
		


private:
	int x_val;
	int y_val;
	bool is_move;
	unsigned int bullet_dir;

};

#endif
