#pragma once

#ifndef TEXT_H_
#define TEXT_H_

#include "CommonFunc.h"

class Text
{
public:
	Text();
	~Text();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
		BLUE_TEXT = 3,
	};

	bool LoadFile(std::string filepath);
	bool LoadText(TTF_Font* font, SDL_Renderer* renderer);
	void Free();
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	void RenderText(SDL_Renderer* renderer, int xp, int yp, SDL_Rect* timeRect);

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}

	void SetText(std::string& text)
	{
		str_val = text;
	}

	std::string getText()
	{
		return str_val;
	}

private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;



};



#endif
