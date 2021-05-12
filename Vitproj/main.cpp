
#include <ctime>
#include <string>
#include <iostream>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "MonstersObject.h"
#include "BatsObject.h"
#include "HouseObject.h"
#include "GameiLLustrate.h"
#include "MonHP.h"
#include "BatHP.h"
#include "Magic2.h"
#include "Laser1.h"
#include "Laser2.h"
#include "Magic1HP.h"
#include "Laser1HP.h"
#include "Laser2HP.h"
#include "Magic2HP.h"
#include "Text.h"
#include "Bullet.h"
#include "Timer.h"


BaseObject g_background;
TTF_Font* font_time;
int ypos[5] = { 45,175,330,500,650 };
int monsters_list_size = 0;
int bats_list_size = 0;



bool initData()
{


	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0) return false;

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow(
		"Viet's Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (g_window == NULL)
		success = false;
	else
	{
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags)) && imgFlags)
				success = false;
		}

		if (TTF_Init() == -1)
			success = false;

		font_time = TTF_OpenFont("font\\39335_UniversCondensed.ttf", 50);
	}
	return success;
}

bool LoadBackground()
{
	bool ret = g_background.LoadIMG("image\\bg.jpg", g_renderer);
	if (ret == false) return false;
	return true;
}

void close()
{
	g_background.Free();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector <MonstersObject*> Make_Monsters_List()
{
	srand(time(NULL));
	std::vector <MonstersObject*> Monsters_List;
	MonstersObject* monsters_obj = new MonstersObject[monsters_list_size];

	for (int i = 0; i < monsters_list_size; i++)
	{
		MonstersObject* p_monster = (monsters_obj + i);
		if (p_monster != NULL)
		{
			p_monster->LoadIMG("image\\mons1.png", g_renderer);
			p_monster->set_clips();
			p_monster->set_x_pos(-rand() % 1000);
			p_monster->set_y_pos(ypos[rand() % 5]);

			Monsters_List.push_back(p_monster);
		}

	}
	return Monsters_List;
}

std::vector <BatsObject*> Make_Bats_List()
{
	std::vector <BatsObject*> Bats_List;
	BatsObject* bat_obj = new BatsObject[bats_list_size];

	for (int i = 0; i < bats_list_size; i++)
	{
		BatsObject* p_bat = (bat_obj + i);
		if (p_bat != NULL)
		{
			p_bat->LoadIMG("image\\bat_right.png", g_renderer);
			p_bat->set_clips();
			p_bat->set_x_pos(-rand() % 1000);
			p_bat->set_y_pos(ypos[rand() % 5]);

			Bullet* p_bullet = new Bullet();

			p_bat->InitBullet(p_bullet, g_renderer);

			Bats_List.push_back(p_bat);
		}

	}
	return Bats_List;
}


int main(int argc, char* argv[])
{
	ImpTimer fps_timer;
	if (initData() == false)
		return -1;
	if (LoadBackground() == false)
		return -1;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) std::cout << Mix_GetError << std::endl;

	SDLCommonFunc::showSDL(g_renderer);

	int remaindertime_menu = 0;
	int remaindertime_gameover = 0;
	int remaindertime_gamewin = 0;
	int menuN = SDLCommonFunc::showMenu(g_renderer, remaindertime_menu);

	MainObject p_player;
	p_player.LoadIMG("image\\sp_left.png", g_renderer);

	p_player.set_clips();

	Text time_game;
	Text score_game;
	time_game.SetColor(Text::BLUE_TEXT);
	score_game.SetColor(Text::BLUE_TEXT);

	GameILL* gameill = new GameILL();
	GameILL hpbar;

	HouseObject* house = new HouseObject();
	HouseObject* ship1 = new HouseObject();
	HouseObject* magictow1 = new HouseObject();
	HouseObject* tesla1 = new HouseObject();
	HouseObject* magictow2 = new HouseObject();
	HouseObject* tesla2 = new HouseObject();


	Magic2* magic2 = new Magic2();
	Laser1* laser1 = new Laser1();
	Laser2* laser2 = new Laser2();

	MonHP* monhp = new MonHP();
	BatHP* bathp = new BatHP();

	Magic1HP* magic1hp = new Magic1HP();
	Laser1HP* laser1hp = new Laser1HP();
	Laser2HP* laser2hp = new Laser2HP();
	Magic2HP* magic2hp = new Magic2HP();


	Bullet* turr_bullet = new Bullet();
	Bullet* turr1_bullet = new Bullet();
	Bullet* turr2_bullet = new Bullet();
	Bullet* turr3_bullet = new Bullet();

	bool bool_magic1 = true;
	bool bool_magic1hp = true;
	bool bool_laser1 = true;
	bool bool_laser1hp = true;
	bool bool_laser2 = true;
	bool bool_laser2hp = true;
	bool bool_magic2 = true;
	bool bool_magic2hp = true;

	magictow1->InitBullet(turr_bullet, g_renderer);
	magic2->InitBullet(turr1_bullet, g_renderer);
	laser1->InitLaser(turr2_bullet, g_renderer);
	laser2->InitLaser(turr3_bullet, g_renderer);


	if (house->LoadIMG("image\\spship.png", g_renderer) == false) return -1;
	if (ship1->LoadIMG("image\\ship1.png", g_renderer) == false) return -1;
	if (magictow1->LoadIMG("image\\magictow.png", g_renderer) == false) return -1;
	if (tesla1->LoadIMG("image\\tesla.png", g_renderer) == false) return -1;
	if (magictow2->LoadIMG("image\\magictow.png", g_renderer) == false) return -1;
	if (tesla2->LoadIMG("image\\tesla.png", g_renderer) == false) return -1;

	int score = 0;

	static int hp_x = 1119;
	static int hp_w = 133;

	double magic1hp_x = 965;
	double magic1hp_w = 70;
	double laser1hp_x = 965;
	double laser1hp_w = 70;
	double laser2hp_x = 875;
	double laser2hp_w = 70;
	double magic2hp_x = 965;
	double magic2hp_w = 70;

	monhp->InitHPbar(g_renderer);
	bathp->InitHPbar(g_renderer);
	hpbar.InitHPbar(g_renderer);
	magic1hp->InitHPbar(g_renderer);
	laser1hp->InitHPbar(g_renderer);
	laser2hp->InitHPbar(g_renderer);
	magic2hp->InitHPbar(g_renderer);

	bool running = true;
	bool gameover_state = false;
	int num_of_dead = 0;


	if (menuN == -1)
	{
		running = false;
		return 0;
	}

	else if (menuN == 2)
	{
		int cslevel = SDLCommonFunc::ChooseLevel(g_renderer);

		switch (cslevel)
		{
		case 1:
			monsters_list_size = 5;
			bats_list_size = 5;
			break;
		case 2:
			monsters_list_size = 40;
			bats_list_size = 40;
			break;
		case 3:
			monsters_list_size = 60;
			bats_list_size = 60;
			break;
		case 4:
			monsters_list_size = 100;
			bats_list_size = 100;
			break;
		}
	}

	std::vector <MonstersObject*> monsters_list = Make_Monsters_List();
	std::vector <BatsObject*> bats_list = Make_Bats_List();

	std::vector <int> pmon(monsters_list_size);
	std::vector <int> monhp_w(monsters_list_size, 70);
	std::vector <int> pbat(bats_list_size);
	std::vector <int> bathp_w(bats_list_size, 70);

	while (running)
	{
		fps_timer.start();
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				g_background.Free();
				p_player.Free();
				running = false;
			}
				
		}
		p_player.HandleInput(g_event, g_renderer);

		SDL_SetRenderDrawColor(g_renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_renderer);
		g_background.Render(g_renderer, NULL);
		p_player.HandleBullet(g_renderer);
		p_player.Show(g_renderer);
		gameill->Initlives(g_renderer, p_player);
		gameill->Show(g_renderer, p_player);
		hpbar.ShowHPbar(g_renderer, hp_x, hp_w);

		house->Show(g_renderer, "1");
		if (bool_magic1) magictow1->Show(g_renderer, "2");
		if (bool_laser1) tesla1->Show(g_renderer, "3");
		if (bool_laser2) tesla2->Show(g_renderer, "4");
		if (bool_magic2) magictow2->Show(g_renderer, "5");
		ship1->Show(g_renderer, "6");

		if (bool_magic1hp) magic1hp->ShowHPbar(g_renderer, magic1hp_x, magic1hp_w);
		if (bool_laser1hp) laser1hp->ShowHPbar(g_renderer, laser1hp_x, laser1hp_w);
		if (bool_laser2hp) laser2hp->ShowHPbar(g_renderer, laser2hp_x, laser2hp_w);
		if (bool_magic2hp) magic2hp->ShowHPbar(g_renderer, magic2hp_x, magic2hp_w);


		magictow1->MakeBullet(g_renderer);
		magic2->MakeBullet(g_renderer);
		laser1->MakeBullet(g_renderer);
		laser2->MakeBullet(g_renderer);

		for (int i = 0; i < monsters_list.size(); i++)
		{

			MonstersObject* p_monster = monsters_list.at(i);
			pmon[i] = p_monster->GetRect().x;
			p_monster->Show(g_renderer);
			monhp->ShowHPbar(g_renderer, p_monster, pmon[i], monhp_w[i]);

			SDL_Rect monster_rect = p_monster->Get_Rect_Frame();
			SDL_Rect rect_player = p_player.Get_Rect_Frame();
			bool bc3 = SDLCommonFunc::CheckdetailedCollision(rect_player, monster_rect, "case 3");


			if (bc3)
			{
				num_of_dead++;
				gameill->Decrease();
				gameill->Render(g_renderer);

				if (num_of_dead >= 4)
				{
					gameover_state = true;
				}
			}

			if (p_monster->get_x_pos() > 950 && p_monster->get_y_pos() > 290 && p_monster->get_y_pos() < 400)
			{
				hp_x++;
				hp_w--;
				p_monster->Free();
				monsters_list.erase(monsters_list.begin() + i);
				pmon.erase(pmon.begin() + i);
				monhp_w.erase(monhp_w.begin() + i);
			}

			else if ((p_monster->get_x_pos() > 830 && p_monster->get_y_pos() < 330) || (p_monster->get_x_pos() > 830 && p_monster->get_y_pos() > 490))
			{
				if (hp_w > 0)
				{
					hp_x++;
					hp_w--;
				}

				if (p_monster->get_y_pos() == 45 && magic1hp_w > 0)
				{
					if (bool_magic1 == true)
					{
						magic1hp_x += 5;
						magic1hp_w -= 5;
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}
					else if (bool_magic1 == false)
					{
						if (p_monster->get_x_pos() > 950)
						{
							magic1hp_x += 5;
							magic1hp_w -= 5;
							p_monster->Free();
							monsters_list.erase(monsters_list.begin() + i);
							pmon.erase(pmon.begin() + i);
							monhp_w.erase(monhp_w.begin() + i);
						}
					}

				}
				else if (p_monster->get_y_pos() == 175 && laser1hp_w > 0)
				{
					if (bool_laser1 == true)
					{
						laser1hp_x += 5;
						laser1hp_w -= 5;
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}
					else if (bool_laser1 == false)
					{
						if (p_monster->get_x_pos() > 950)
						{
							laser1hp_x += 5;
							laser1hp_w -= 5;
							p_monster->Free();
							monsters_list.erase(monsters_list.begin() + i);
							pmon.erase(pmon.begin() + i);
							monhp_w.erase(monhp_w.begin() + i);
						}
					}
				}
				else if (p_monster->get_y_pos() == 500 && laser2hp_w > 0)
				{
					if (bool_laser2 == true)
					{
						laser2hp_x += 5;
						laser2hp_w -= 5;
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}
					else if (bool_laser2 == false)
					{
						if (p_monster->get_x_pos() > 950)
						{
							laser2hp_x += 5;
							laser2hp_w -= 5;
							p_monster->Free();
							monsters_list.erase(monsters_list.begin() + i);
							pmon.erase(pmon.begin() + i);
							monhp_w.erase(monhp_w.begin() + i);
						}
					}
				}
				else if (p_monster->get_y_pos() == 650 && magic2hp_w > 0)
				{
					if (bool_magic2 == true)
					{
						magic2hp_x += 5;
						magic2hp_w -= 5;
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}
					else if (bool_magic2 == false)
					{
						if (p_monster->get_x_pos() > 950)
						{
							magic2hp_x += 5;
							magic2hp_w -= 5;
							p_monster->Free();
							monsters_list.erase(monsters_list.begin() + i);
							pmon.erase(pmon.begin() + i);
							monhp_w.erase(monhp_w.begin() + i);
						}
					}
				}

			}

			std::vector <Bullet*> magictow1_bullet = magictow1->get_bullet_list();
			std::vector <Bullet*> laser1_bullet = laser1->get_bullet_list();
			std::vector <Bullet*> laser2_bullet = laser2->get_bullet_list();
			std::vector <Bullet*> magic2_bullet = magic2->get_bullet_list();


			for (int j = 0; j < magictow1_bullet.size(); j++)
			{
				Bullet* m1_bullet = magictow1_bullet.at(j);
				bool bcc = SDLCommonFunc::CheckdetailedCollision(monster_rect, m1_bullet->GetRect(), "case 1");
				if (bcc)
				{
					if (monhp_w[i] > 0)
					{
						pmon[i] += 5;
						monhp_w[i] -= 5;
						if ((int)(SDL_GetTicks()) % 2 == 0)
						{
							m1_bullet->set_is_move(true);
							m1_bullet->SetRect(860, -10);
						}
						else
						{
							m1_bullet->SetRect(860, -10);
							m1_bullet->set_is_move(false);
						}
					}

					if (monhp_w[i] <= 0)
					{
						p_monster->LoadMonsDyingSound();
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);

					}

				}
			}

			for (int j = 0; j < laser1_bullet.size(); j++)
			{
				Bullet* l1_bullet = laser1_bullet.at(j);
				bool bcc1 = SDLCommonFunc::CheckdetailedCollision(monster_rect, l1_bullet->GetRect(), "case 1");
				if (bcc1)
				{
					if (monhp_w[i] > 0)
					{
						pmon[i] += 5;
						monhp_w[i] -= 5;

						if ((int)(SDL_GetTicks()) % 2 == 0)
						{
							l1_bullet->set_is_move(true);
							l1_bullet->SetRect(860, 100);
						}
						else
						{
							l1_bullet->SetRect(860, 100);
							l1_bullet->set_is_move(false);
						}

					}

					if (monhp_w[i] <= 0)
					{
						p_monster->LoadMonsDyingSound();
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}

				}
			}

			for (int j = 0; j < laser2_bullet.size(); j++)
			{
				Bullet* l2_bullet = laser2_bullet.at(j);
				bool bcc3 = SDLCommonFunc::CheckdetailedCollision(monster_rect, l2_bullet->GetRect(), "case 1");
				if (bcc3)
				{
					if (monhp_w[i] > 0)
					{
						pmon[i] += 5;
						monhp_w[i] -= 5;

						if ((int)(SDL_GetTicks()) % 2 == 0)
						{
							l2_bullet->set_is_move(true);
							l2_bullet->SetRect(860, 400);
						}
						else
						{
							l2_bullet->SetRect(860, 400);
							l2_bullet->set_is_move(false);
						}

					}

					if (monhp_w[i] <= 0)
					{
						p_monster->LoadMonsDyingSound();
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}

				}
			}

			for (int j = 0; j < magic2_bullet.size(); j++)
			{
				Bullet* m2_bullet = magic2_bullet.at(j);
				bool bcc4 = SDLCommonFunc::CheckdetailedCollision(monster_rect, m2_bullet->GetRect(), "case 1");
				if (bcc4)
				{
					if (monhp_w[i] > 0)
					{
						pmon[i] += 5;
						monhp_w[i] -= 5;

						if ((int)(SDL_GetTicks()) % 2 == 0)
						{
							m2_bullet->set_is_move(true);
							m2_bullet->SetRect(860, 610);
						}
						else
						{
							m2_bullet->SetRect(860, 610);
							m2_bullet->set_is_move(false);
						}

					}

					if (monhp_w[i] <= 0)
					{
						p_monster->LoadMonsDyingSound();
						p_monster->Free();
						monsters_list.erase(monsters_list.begin() + i);
						pmon.erase(pmon.begin() + i);
						monhp_w.erase(monhp_w.begin() + i);
					}

				}
			}
		}

		for (int i = 0; i < bats_list.size(); i++)
		{
			BatsObject* p_bat = bats_list.at(i);
			if (bats_list.at(i)->get_x_pos() >= 0)
			{
				if (p_bat->get_y_pos() == 45)
				{
					p_bat->MakeBullet1(g_renderer, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50, hp_x, hp_w, magic1hp_x, magic1hp_w, bool_magic1);
				}
				if (p_bat->get_y_pos() == 175)
				{
					p_bat->MakeBullet1(g_renderer, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50, hp_x, hp_w, laser1hp_x, laser1hp_w, bool_laser1);
				}
				if (p_bat->get_y_pos() == 500)
				{
					p_bat->MakeBullet1(g_renderer, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50, hp_x, hp_w, laser2hp_x, laser2hp_w, bool_laser2);
				}
				if (p_bat->get_y_pos() == 650)
				{
					p_bat->MakeBullet1(g_renderer, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50, hp_x, hp_w, magic2hp_x, magic2hp_w, bool_magic2);
				}
				if (p_bat->get_y_pos() == 330)
				{
					p_bat->MakeBullet2(g_renderer, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 50, hp_x, hp_w);
				}
			}


			p_bat->Show(g_renderer);
			pbat[i] = p_bat->GetRect().x;
			bathp->ShowHPbar(g_renderer, p_bat, pbat[i], bathp_w[i]);

			SDL_Rect rect_player = p_player.Get_Rect_Frame();
			bool bc1 = false;

			std::vector <Bullet*> bat_bullet = p_bat->get_bullet_list();

			for (int j = 0; j < bat_bullet.size(); j++)
			{
				Bullet* p_bullet = bat_bullet.at(j);
				bc1 = SDLCommonFunc::CheckdetailedCollision(p_bullet->GetRect(), rect_player, "case 1");

				if (bc1)
				{
					num_of_dead++;
					gameill->Decrease();
					gameill->Render(g_renderer);
					if ((int)(SDL_GetTicks() / 1000) % 3 == 0)
					{
						bat_bullet.at(j)->set_is_move(true);
						bat_bullet.at(j)->SetRect(p_bat->get_x_pos() + 20, p_bat->get_y_pos() - 10);
					}
					else
					{
						bat_bullet.at(j)->SetRect(p_bat->get_x_pos() + 20, p_bat->get_y_pos() - 10);
						bat_bullet.at(j)->set_is_move(false);
					}
				}
			}

			SDL_Rect rect_bats = p_bat->Get_Rect_Frame();
			bool bc2 = SDLCommonFunc::CheckdetailedCollision(rect_player, rect_bats, "case 2");
			if (bc1 || bc2)
			{
				if (num_of_dead >= 4)
				{
					gameover_state = true;
				}	
			}

			if (p_bat->get_x_pos() > 830)
			{
				if (p_bat->get_y_pos() == 45)
				{
					if (bool_magic1 == true)
					{
						hp_x++;
						hp_w--;
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}
					else if (bool_magic1 == false)
					{
						if (p_bat->get_x_pos() > 950)
						{
							hp_x++;
							hp_w--;
							p_bat->Free();
							bats_list.erase(bats_list.begin() + i);
							pbat.erase(pbat.begin() + i);
							bathp_w.erase(bathp_w.begin() + i);
						}
					}
				}
				else if (p_bat->get_y_pos() == 175)
				{
					if (bool_laser1 == true)
					{
						hp_x++;
						hp_w--;
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}
					else if (bool_laser1 == false)
					{
						if (p_bat->get_x_pos() > 950)
						{
							hp_x++;
							hp_w--;
							p_bat->Free();
							bats_list.erase(bats_list.begin() + i);
							pbat.erase(pbat.begin() + i);
							bathp_w.erase(bathp_w.begin() + i);
						}
					}
				}
				else if (p_bat->get_y_pos() == 500)
				{
					if (bool_laser2 == true)
					{
						hp_x++;
						hp_w--;
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}
					else if (bool_laser2 == false)
					{
						if (p_bat->get_x_pos() > 950)
						{
							hp_x++;
							hp_w--;
							p_bat->Free();
							bats_list.erase(bats_list.begin() + i);
							pbat.erase(pbat.begin() + i);
							bathp_w.erase(bathp_w.begin() + i);
						}
					}
				}
				else if (p_bat->get_y_pos() == 650)
				{
					if (bool_magic2 == true)
					{
						hp_x++;
						hp_w--;
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}
					else if (bool_magic2 == false)
					{
						if (p_bat->get_x_pos() > 950)
						{
							hp_x++;
							hp_w--;
							p_bat->Free();
							bats_list.erase(bats_list.begin() + i);
							pbat.erase(pbat.begin() + i);
							bathp_w.erase(bathp_w.begin() + i);
						}
					}
				}
				else if (p_bat->get_y_pos() == 330)
				{
					if (p_bat->get_x_pos() > 950)
					{
						hp_x++;
						hp_w--;
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}
				}

			}

			std::vector <Bullet*> magictow1_bullet = magictow1->get_bullet_list();
			std::vector <Bullet*> laser1_bullet = laser1->get_bullet_list();
			std::vector <Bullet*> laser2_bullet = laser2->get_bullet_list();
			std::vector <Bullet*> magic2_bullet = magic2->get_bullet_list();


			for (int j = 0; j < magictow1_bullet.size(); j++)
			{
				Bullet* m1_bullet = magictow1_bullet.at(j);
				bool bcc = SDLCommonFunc::CheckCollision(rect_bats, m1_bullet->GetRect());
				if (bcc)
				{
					if (bathp_w[i] > 0)
					{
						pbat[i] += 8;
						bathp_w[i] -= 8;

						if ((int)(SDL_GetTicks() / 1000) % 2 == 0)
						{
							m1_bullet->set_is_move(true);
							m1_bullet->SetRect(860, -10);
						}
						else
						{
							m1_bullet->SetRect(860, -10);
							m1_bullet->set_is_move(false);
						}
					}

					if (bathp_w[i] <= 0)
					{
						p_bat->LoadBatsDyingSound();
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}

				}
			}

			for (int j = 0; j < laser1_bullet.size(); j++)
			{
				Bullet* l1_bullet = laser1_bullet.at(j);
				bool bcc1 = SDLCommonFunc::CheckCollision(rect_bats, l1_bullet->GetRect());
				if (bcc1)
				{
					if (bathp_w[i] > 0)
					{
						pbat[i] += 8;
						bathp_w[i] -= 8;

						if ((int)(SDL_GetTicks() / 1000) % 2 == 0)
						{
							l1_bullet->set_is_move(true);
							l1_bullet->SetRect(860, 100);
						}
						else
						{
							l1_bullet->SetRect(860, 100);
							l1_bullet->set_is_move(false);
						}
					}

					if (bathp_w[i] <= 0)
					{
						p_bat->LoadBatsDyingSound();
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}

				}
			}

			for (int j = 0; j < laser2_bullet.size(); j++)
			{
				Bullet* l2_bullet = laser2_bullet.at(j);
				bool bcc3 = SDLCommonFunc::CheckCollision(rect_bats, l2_bullet->GetRect());
				if (bcc3)
				{
					if (bathp_w[i] > 0)
					{
						pbat[i] += 8;
						bathp_w[i] -= 8;

						if ((int)(SDL_GetTicks() / 1000) % 2 == 0)
						{
							l2_bullet->set_is_move(true);
							l2_bullet->SetRect(860, 400);
						}
						else
						{
							l2_bullet->SetRect(860, 400);
							l2_bullet->set_is_move(false);
						}

					}

					if (bathp_w[i] <= 0)
					{
						p_bat->LoadBatsDyingSound();
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}

				}
			}
			for (int j = 0; j < magic2_bullet.size(); j++)
			{
				Bullet* m2_bullet = magic2_bullet.at(j);
				bool bcc4 = SDLCommonFunc::CheckCollision(rect_bats, m2_bullet->GetRect());
				if (bcc4)
				{
					if (bathp_w[i] > 0)
					{
						pbat[i] += 8;
						bathp_w[i] -= 8;

						if ((int)(SDL_GetTicks() / 1000) % 2 == 0)
						{
							m2_bullet->set_is_move(true);
							m2_bullet->SetRect(860, 610);
						}
						else
						{
							m2_bullet->SetRect(860, 610);
							m2_bullet->set_is_move(false);
						}

					}

					if (bathp_w[i] <= 0)
					{
						p_bat->LoadBatsDyingSound();
						p_bat->Free();
						bats_list.erase(bats_list.begin() + i);
						pbat.erase(pbat.begin() + i);
						bathp_w.erase(bathp_w.begin() + i);
					}

				}
			}
		}

		std::vector <Bullet*> Bullet_arr = p_player.get_bullet_list();
		for (int i = 0; i < Bullet_arr.size(); i++)
		{
			Bullet* bullet = Bullet_arr.at(i);
			if (bullet != NULL)
			{
				for (int j = 0; j < monsters_list.size(); j++)
				{
					MonstersObject* monster_threat = monsters_list[j];

					if (monster_threat != NULL)
					{
						SDL_Rect threat_rect;
						threat_rect.x = monster_threat->GetRect().x;
						threat_rect.y = monster_threat->GetRect().y;
						threat_rect.w = monster_threat->get_width_frame();
						threat_rect.h = monster_threat->get_height_frame();

						SDL_Rect bullet_rect = bullet->GetRect();

						bool bc = SDLCommonFunc::CheckCollision(threat_rect, bullet_rect);
						if (bc)
						{
							p_player.RemoveBullet(i);
							if (monhp_w[j] > 0)
							{
								pmon[j] += 3;
								monhp_w[j] -= 3;
							}
							if (monhp_w[j] <= 0)
							{
								monster_threat->LoadMonsDyingSound();
								monster_threat->Free();
								monsters_list.erase(monsters_list.begin() + j);
								pmon.erase(pmon.begin() + j);
								monhp_w.erase(monhp_w.begin() + j);
								score += 10;
							}
						}
					}
				}


				for (int j = 0; j < bats_list.size(); j++)
				{
					BatsObject* bat_threat = bats_list[j];

					if (bat_threat != NULL)
					{
						SDL_Rect bat_rect;
						bat_rect.x = bat_threat->GetRect().x;
						bat_rect.y = bat_threat->GetRect().y;
						bat_rect.w = bat_threat->get_width_frame();
						bat_rect.h = bat_threat->get_height_frame();

						SDL_Rect bullet_rect = bullet->GetRect();

						bool bc = SDLCommonFunc::CheckCollision(bat_rect, bullet_rect);
						if (bc)
						{
							p_player.RemoveBullet(i);
							if (bathp_w[j] > 0)
							{
								pbat[j] += 10;
								bathp_w[j] -= 10;
							}
							if (bathp_w[j] <= 0)
							{
								bat_threat->LoadBatsDyingSound();
								bat_threat->Free();
								bats_list.erase(bats_list.begin() + j);
								pbat.erase(pbat.begin() + j);
								bathp_w.erase(bathp_w.begin() + j);
								score += 5;
							}
						}
					}
				}
			}
		}



		if (magic1hp_w <= 0)
		{
			bool_magic1 = false;
			bool_magic1hp = false;

		}
		if (laser1hp_w <= 0)
		{
			bool_laser1 = false;
			bool_laser1hp = false;
		}
		if (laser2hp_w <= 0)
		{
			bool_laser2 = false;
			bool_laser2hp = false;
		}
		if (magic2hp_w <= 0)
		{
			bool_magic2 = false;
			bool_magic2hp = false;
		}

		if (hp_w <= 0)
		{
			gameover_state = true;
		}

		int hour = 0;
		int minute = 0;
		int second = 0;
		std::string TimePassed = "";
		Uint32 timeval = (SDL_GetTicks() / 1000) - remaindertime_menu - remaindertime_gameover - remaindertime_gamewin;
		hour = timeval / 3600;
		minute = (timeval - (hour * 3600)) / 60;
		second = timeval - (hour * 3600) - (minute * 60);
		TimePassed = "Time: " + std::to_string(hour) + ':' + std::to_string(minute) + ":" + std::to_string(second);
		SDL_Rect timeRect;
		timeRect.w = 200;
		timeRect.h = 50;
		timeRect.x = 50;
		timeRect.y = 270;

		time_game.SetText(TimePassed);
		time_game.LoadText(font_time, g_renderer);
		time_game.RenderText(g_renderer, 650, 0, &timeRect);

		std::string Score = "Score: " + std::to_string(score);
		SDL_Rect scoreRect;
		scoreRect.w = 175;
		scoreRect.h = 50;
		scoreRect.x = 50;
		scoreRect.y = 270;

		score_game.SetText(Score);
		score_game.LoadText(font_time, g_renderer);
		score_game.RenderText(g_renderer, 400, 0, &scoreRect);


		SDL_RenderPresent(g_renderer);

		int real_time = fps_timer.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_time;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}

		if (monsters_list.size() == 0 && bats_list.size() == 0)
		{
			int g_w = SDLCommonFunc::showWin(g_renderer, score, remaindertime_gamewin);
			if (g_w == 0)
			{
				int cslevel = SDLCommonFunc::ChooseLevel(g_renderer);

				switch (cslevel)
				{
				case 1:
					monsters_list_size = 5;
					bats_list_size = 5;
					break;
				case 2:
					monsters_list_size = 40;
					bats_list_size = 40;
					break;
				case 3:
					monsters_list_size = 60;
					bats_list_size = 60;
					break;
				case 4:
					monsters_list_size = 100;
					bats_list_size = 100;
					break;
				}

				num_of_dead = 0;
				gameover_state = false;
				gameill->Set_size_pos_list();
				gameill->set_number();
				score = 0;

				for (int i = 0; i < monsters_list.size(); i++)
				{
					monsters_list.erase(monsters_list.begin() + i);
				}

				for (int i = 0; i < bats_list.size(); i++)
				{
					bats_list.erase(bats_list.begin() + i);
				}

				monsters_list = Make_Monsters_List();
				bats_list = Make_Bats_List();

				pmon.resize(monsters_list_size);
				monhp_w.resize(monsters_list_size);
				pbat.resize(bats_list_size);
				bathp_w.resize(bats_list_size);

				for (int i = 0; i < monsters_list_size; i++)
				{
					monhp_w[i] = 70;
					bathp_w[i] = 70;
				}

				hp_x = 1119;
				hp_w = 133;
				magic1hp_x = 965;
				magic1hp_w = 70;
				laser1hp_x = 965;
				laser1hp_w = 70;
				laser2hp_x = 875;
				laser2hp_w = 70;
				magic2hp_x = 965;
				magic2hp_w = 70;
				bool_laser1 = true;
				bool_laser1hp = true;
				bool_laser2 = true;
				bool_laser2hp = true;
				bool_magic1 = true;
				bool_magic1hp = true;
				bool_magic2 = true;
				bool_magic2hp = true;
			}
			else if (g_w == 2 || g_w  == 1)
			{
				return 0;
			}
		}
		
		if (gameover_state == true)
		{
			int gameover_c = SDLCommonFunc::showEnd(g_renderer, score, remaindertime_gameover);
			if (gameover_c == 1)
			{
				running = false;
			}
			else if (gameover_c == 0)
			{
				int cslevel = SDLCommonFunc::ChooseLevel(g_renderer);

				switch (cslevel)
				{
				case 1:
					monsters_list_size = 5;
					bats_list_size = 5;
					break;
				case 2:
					monsters_list_size = 40;
					bats_list_size = 40;
					break;
				case 3:
					monsters_list_size = 60;
					bats_list_size = 60;
					break;
				case 4:
					monsters_list_size = 100;
					bats_list_size = 100;
					break;
				}
				num_of_dead = 0;
				gameover_state = false;
				gameill->Set_size_pos_list();
				gameill->set_number();
				score = 0;

				for (int i = 0; i < monsters_list.size(); i++)
				{
					monsters_list.erase(monsters_list.begin() + i);
				}

				for (int i = 0; i < bats_list.size(); i++)
				{
					bats_list.erase(bats_list.begin() + i);
				}

				monsters_list = Make_Monsters_List();
				bats_list = Make_Bats_List();

				pmon.resize(monsters_list_size);
				monhp_w.resize(monsters_list_size);
				pbat.resize(bats_list_size);
				bathp_w.resize(bats_list_size);
	
				for (int i = 0; i < monsters_list_size; i++)
				{
					monhp_w[i] = 70;
					bathp_w[i] = 70;
				}

				hp_x = 1119;
				hp_w = 133;
				magic1hp_x = 965;
				magic1hp_w = 70;
				laser1hp_x = 965;
				laser1hp_w = 70;
				laser2hp_x = 875;
				laser2hp_w = 70;
				magic2hp_x = 965;
				magic2hp_w = 70;
				bool_laser1 = true;
				bool_laser1hp = true;
				bool_laser2 = true;
				bool_laser2hp = true;
				bool_magic1 = true;
				bool_magic1hp = true;
				bool_magic2 = true;
				bool_magic2hp = true;
			}
		}
	}

	close();
	return 0;
}


