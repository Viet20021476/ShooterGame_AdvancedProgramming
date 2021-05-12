
#pragma once

#ifndef BAT_HP_H_
#define BAT_HP_H_

#include "BaseObject.h"
#include "BatsObject.h"

class BatHP : public BaseObject
{
public:
	BatHP();
	~BatHP();

	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer, BatsObject* p_bat, int hp_x, int hp_w);
};


#endif
