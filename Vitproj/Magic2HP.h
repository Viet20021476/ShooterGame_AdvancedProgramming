
#pragma once

#ifndef MAGIC2_HP_H_
#define MAGIC2_HP_H_

#include "BaseObject.h"


class Magic2HP : public BaseObject
{
public:
	Magic2HP();
	~Magic2HP();

	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer, double& magic2hp_x, double& magic2hp_w);
};


#endif
