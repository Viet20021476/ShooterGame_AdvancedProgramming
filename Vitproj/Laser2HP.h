
#pragma once

#ifndef LASER2_HP_H_
#define LASER2_HP_H_

#include "BaseObject.h"

class Laser2HP : public BaseObject
{
public:
	Laser2HP();
	~Laser2HP();

	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer, double& laser2hp_x, double& laser2hp_w);
};


#endif
