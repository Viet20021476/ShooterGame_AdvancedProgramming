
#include "MonstersObject.h"

MonstersObject::MonstersObject()
{
	width_frame = 0;
	height_frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	frame_ = 0;
}

MonstersObject::~MonstersObject()
{

}

bool MonstersObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadIMG(path, screen);
	if (ret == true)
	{
		width_frame = rect_.w / 5;
		height_frame = rect_.h;
	}
	return ret;
}

SDL_Rect MonstersObject::Get_Rect_Frame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame;
	rect.h = height_frame;

	return rect;
}

void MonstersObject::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 5; i++)
		{
			frame_clips[i].x = i * width_frame ;
			frame_clips[i].y = 0;
			frame_clips[i].w = width_frame;
			frame_clips[i].h = height_frame;
		}
	}
}

void MonstersObject::Show(SDL_Renderer* des)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	frame_ = (SDL_GetTicks() / 100) % 3;
	x_pos += 2;

	if (frame_ >= 4)
		frame_ = 0;

	SDL_Rect* currentClip = &frame_clips[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, 110, 110 };
	SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);

}

void MonstersObject::LoadMonsDyingSound()
{
	Mix_Chunk* soundEffect = Mix_LoadWAV("sound\\mons_dying.wav");
	Mix_PlayChannel(-1, soundEffect, 0);
}
