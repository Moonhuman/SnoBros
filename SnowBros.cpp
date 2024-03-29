// SnowBros.cpp: 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "Stage.h"
#include "Gift.h"
#include "BigBall.h"
#include "Monster.h"
#include "Player.h"
#include "Snowball.h"
#include "Boss.h"

IMAGE background_img, title_img, begin_img, game_help_img, move_rule_img;
IMAGE return_img, onemode_img, twomode_img, pass_level, fail_level, life_img[2];
int player_cnt = 0;

void ShowMenu()
{
	putimage(0, 0, &background_img);
	//putimage(4 * UNIT, UNIT, &title_img);
	putimage(8 * UNIT, 10 * UNIT, &begin_img);
	putimage(8 * UNIT, 12 * UNIT, &game_help_img);
}

void ShowHelp()
{
	putimage(0, 0, &background_img);
	putimage(100, 100, &move_rule_img);
	putimage(22 * UNIT, 0, &return_img);
}

void ShowMode()
{
	putimage(0, 0, &background_img);
	putimage(22 * UNIT, 0, &return_img);
	putimage(10 * UNIT, 10 * UNIT, &onemode_img);
	putimage(10 * UNIT, 12 * UNIT, &twomode_img);
}

vector<char> MyKbHit()
{
	vector<char> ret;
	if (GetAsyncKeyState('A') < 0)
		ret.push_back('a');
	if (GetAsyncKeyState('D') < 0)
		ret.push_back('d');
	if (GetAsyncKeyState('J') < 0)
		ret.push_back('j');
	if (GetAsyncKeyState('K') < 0)
		ret.push_back('k');
	if (GetAsyncKeyState(VK_LEFT) < 0)
		ret.push_back('<');
	if (GetAsyncKeyState(VK_RIGHT) < 0)
		ret.push_back('>');
	if (GetAsyncKeyState(VK_NUMPAD2) < 0)
		ret.push_back('2');
	if (GetAsyncKeyState(VK_NUMPAD3) < 0)
		ret.push_back('3');
	return ret;
}
wstring GetLife(int a)
{
	wstring res = L"X";
	return res + to_wstring(a);
}
void LoadMap(Stage &gk, vector<Player> &pl)
{
	putimage(0, 0, &gk.back_img);
	for (int i = 1; i < 14; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (gk.mp[i][j] == '#')
				putimage(j * UNIT, i * UNIT, &gk.block_img);
		}
	}
	wstring tmp = L"第" + to_wstring(gk.level) + L"关";
	outtextxy(0, 0, tmp.c_str());
	outtextxy(200, 0, _T("P1:"));
	putimage(300, 0, &life_img[0], NOTSRCERASE);
	putimage(300, 0, &life_img[1], SRCINVERT);
	outtextxy(350, 0, GetLife(pl[1].life).c_str());
	if (player_cnt == 2)
	{
		outtextxy(500, 0, _T("P2:"));
		putimage(600, 0, &life_img[0], NOTSRCERASE);
		putimage(600, 0, &life_img[1], SRCINVERT);
		outtextxy(650, 0, GetLife(pl[2].life).c_str());
	}
}
extern vector<Player> InitPlayer(Stage &gk, int mode);
extern void LoadPlayer(vector<Player> &player);
extern void ControlPlayer(Player &pl, char hit, queue<SnowBall> &q, vector<Monster> &mon, vector<Bigball> &bb);
extern void SnowBallNewPos(queue<SnowBall> &q);
extern vector<Monster> InitMonster(Stage &gk);
extern void LoadMonster(vector<Monster> &monster);
extern void GuideMonster(vector<Monster> &monster, Stage &gk);
extern void MonsterNewPos(Monster &monster, Stage &gk);
extern void KillMonster(vector<Bigball> &bb, vector<Monster> &mon, vector<Monster> &gift);
extern void LoadBigball(vector<Bigball> &bb);
extern void ControlBigBall(vector<Bigball> &bb, Stage &gk);
extern void BigBallNewPos(vector<Bigball> &bb, vector<Gift> &gift);
extern void KillPlayer(vector<Monster> &mon, vector<Player> &pl);
extern void LoadGift(vector<Gift> &gift);
extern void EatGift(Player &pl, vector<Gift> &gift, vector<Monster> &mon);
extern bool LastLevel(int life1, int life2);

bool GoGoGo(int level, int &life1, int &life2)
{
	Stage gk;
	gk.Init(level);
	vector<Player> player = InitPlayer(gk, player_cnt);
	player[1].life = life1;
	player[2].life = life2;
	vector<Monster> monster = InitMonster(gk);
	vector<Bigball> bb;
	queue<SnowBall> ball;
	vector<Gift> gift;
	vector<char> hit;
	BeginBatchDraw();

	/*
	ofstream dd;
	dd.open("dd.txt");
	for (int i = 0; i < monster.size(); i++)
		dd << monster[i].bigball << endl;
	return 0;
	*/

	int ret_cnt = 0;
	while (1)
	{
		LoadMap(gk, player);
		LoadPlayer(player);
		LoadMonster(monster);
		LoadSnowBall(ball);
		LoadGift(gift);
		LoadBigball(bb);

		FlushBatchDraw();
		//LoadBar();
		//LoadMonster();
		hit = MyKbHit();
		if (hit.size())
		{
			for (int i = 0; i < hit.size(); i++)
			{
				if (player[1].life && hit[i] == 'a' || hit[i] == 'd' || hit[i] == 'j' || hit[i] == 'k')
					ControlPlayer(player[1], hit[i], ball, monster, bb);
				else if (player[2].life && player_cnt == 2)
				{
					if (hit[i] == '<')
						hit[i] = 'a';
					else if (hit[i] == '>')
						hit[i] = 'd';
					else if (hit[i] == '2')
						hit[i] = 'j';
					else if (hit[i] == '3')
						hit[i] = 'k';
					ControlPlayer(player[2], hit[i], ball, monster, bb);
				}
			}
		}
		for (int i = 1; i < player.size(); i++)
			if (player[i].life)
				PlayerNewPos(player[i], gk);
		for (int i = 1; i < player.size(); i++)
			EatGift(player[i], gift, monster);
		GuideMonster(monster, gk);
		for (int i = 0; i < monster.size(); i++)
			MonsterNewPos(monster[i], gk);
		SnowBallNewPos(ball);
		
		FreezeMonster(ball, monster);
		KillMonster(bb, monster, gift);
		KillPlayer(monster, player);

		ControlBigBall(bb, gk);
		BigBallNewPos(bb, gift);

		if (!monster.size() && !bb.size())
		{
			if (ret_cnt == 200)
				break;
			ret_cnt++;
		}
		if (player_cnt == 1 && !player[1].life)
		{
			if (ret_cnt == 200)
			{
				EndBatchDraw();
				life1 = player[1].life;
				life2 = player[2].life;
				return false;
			}
			++ret_cnt;
		}
		if (player_cnt == 2 && !player[1].life && !player[2].life)
		{
			if (ret_cnt == 200)
			{
				EndBatchDraw();
				life1 = player[1].life;
				life2 = player[2].life;
				return false;
			}
			++ret_cnt;
		}
		Sleep(10);
	}
	EndBatchDraw();
	life1 = player[1].life;
	life2 = player[2].life;
	return true;
}

void BeginGame()
{
	int level = 1, life1 = 5, life2 = 5;
	while (level <= 15) //关卡总数
	{
		if (GoGoGo(level, life1, life2))
		{
			level++;
			putimage(400, 300, &pass_level);
			Sleep(2000);
		}
		else
		{
			putimage(400, 300, &fail_level);
			Sleep(2000);
			break;
		}
		if (!life1)
			++life1;
		if (!life2)
			++life2;
	}
	if (level == 16) //关卡总数
	{
		if (LastLevel(life1, life2, player_cnt))
		{
			IMAGE all_pass;
			loadimage(&all_pass, _T(".\\img\\all_pass.png"));
			putimage(400, 300, &all_pass);
			Sleep(2000);
		}
	}
	return;
}

//判断鼠标是否点击到图片上，（left，up）为putimage的左上角
bool ClickOn(MOUSEMSG m, IMAGE a, int left, int up)
{
	int x = m.x, y = m.y;
	int right = left + a.getwidth(), down = up + a.getheight();
	if (left <= x && x <= right && up <= y && y <= down)
		return true;
	return false;
}

void InitLoadImage()
{
	srand(time(NULL));
	settextstyle(50, 0, _T("宋体")); //初始化字体
	loadimage(&background_img, _T(".\\img\\background.jpg"));
	loadimage(&title_img, _T(".\\img\\title.bmp"));
	loadimage(&begin_img, _T(".\\img\\begin_game.bmp"));
	loadimage(&game_help_img, _T(".\\img\\game_help.bmp"));
	loadimage(&move_rule_img, _T(".\\img\\move_rule.bmp"));
	loadimage(&return_img, _T(".\\img\\return.jpg"));
	loadimage(&onemode_img, _T(".\\img\\onemode.bmp"));
	loadimage(&twomode_img, _T(".\\img\\twomode.bmp"));
	loadimage(&pass_level, _T(".\\img\\pass_level.bmp"));
	loadimage(&fail_level, _T(".\\img\\fail_level.bmp"));
	loadimage(&life_img[0], _T(".\\img\\life-0.png"));
	loadimage(&life_img[1], _T(".\\img\\life-1.png"));
}

int main()
{
	// for debug
	/*
	initgraph(1200, 700);
	wstring s = L"hello world";
	outtext(s.c_str());
	getchar();
	return 0;
	*/

	initgraph(1200, 700);	// 创建绘图窗口，大小为 1200*700 像素
	InitLoadImage();
	MOUSEMSG click;
	while (1)
	{
		ShowMenu();
		while (1)
		{
			click = GetMouseMsg();
			if (click.mkLButton == true)
				break;
		}
		if (ClickOn(click, begin_img, 8 * UNIT, 10 * UNIT))
		{
			ShowMode(); //选择游戏模式
			player_cnt = 0;
			while (1)
			{
				click = GetMouseMsg();
				if (click.mkLButton == true)
				{
					if (ClickOn(click, onemode_img, 10 * UNIT, 10 * UNIT))
						player_cnt = 1;
					else if (ClickOn(click, twomode_img, 10 * UNIT, 12 * UNIT))
						player_cnt = 2;
					else if (ClickOn(click, return_img, 22 * UNIT, 0))
						break; //返回菜单
				}
				if (player_cnt)
				{
					BeginGame();
					break;
				}
			}
		}
		else if (ClickOn(click, game_help_img, 8 * UNIT, 12 * UNIT))
		{
			ShowHelp(); //查看游戏帮助
			while (1)
			{
				click = GetMouseMsg();
				if (click.mkLButton == true && ClickOn(click, return_img, 22 * UNIT, 0))
					break;
			}
		}
	}


	getchar();
	closegraph();			// 关闭绘图窗口
    return 0;
}

