#pragma once

#ifndef MON_HP_H_
#define MON_HP_H_

#include "BaseObject.h"
#include "MonstersObject.h"

class MonHP : public BaseObject
{
public:
	MonHP();
	~MonHP();
	
	void InitHPbar(SDL_Renderer* renderer);
	void ShowHPbar(SDL_Renderer* renderer, MonstersObject* p_monster, int hp_x,int hp_w);
};


#endif