#include "Text.h"

Text::Text()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
}

Text::~Text()
{
	
}

bool Text::LoadText(TTF_Font* font, SDL_Renderer* renderer)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	width = text_surface->w;
	height = text_surface->h;

	SDL_FreeSurface(text_surface);

	return texture != nullptr;
}

void Text::Free()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Text::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void Text::SetColor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}

	else if (type == BLUE_TEXT)
	{
		SDL_Color color = { 0,0,150 };
		text_color = color;
	}

	if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void Text::RenderText(SDL_Renderer* renderer, int xp, int yp, SDL_Rect* timeRect)
{
	SDL_Rect rquad = { xp,yp,width,height };
	rquad.w = timeRect->w;
	rquad.h = timeRect->h;

	SDL_RenderCopy(renderer, texture, NULL, &rquad);

}

