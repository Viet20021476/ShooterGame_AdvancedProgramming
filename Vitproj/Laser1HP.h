
#pragma once

#ifndef LASER1_HP_H_
#define LASER1_HP_H_

#include "BaseObject.h"

class Laser1HP : public BaseObject
{
public:
	Laser1HP();
	~Laser1HP();

	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer, double& laser1hp_x, double& laser1hp_w);
};


#endif
