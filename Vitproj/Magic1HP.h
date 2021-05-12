
#pragma once

#ifndef MAGIC1_HP_H_
#define MAGIC1_HP_H_

#include "BaseObject.h"
#include "HouseObject.h"

class Magic1HP : public BaseObject
{
public:
	Magic1HP();
	~Magic1HP();

	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer, double& magic1hp_x, double& magic1hp_w);
};


#endif
