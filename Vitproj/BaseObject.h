#pragma once

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	 BaseObject();
	~BaseObject();


	void SetRect(const int& x, const int& y)
	{
		rect_.x = x;
		rect_.y = y;
	}
	SDL_Rect GetRect() const
	{
		return rect_;
	}
	SDL_Texture* GetObject() const
	{
		return p_object_;
	}

	virtual bool LoadIMG(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void RenderHelp(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();


protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;

};




#endif
