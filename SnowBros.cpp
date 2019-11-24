// SnowBros.cpp: 定义控制台应用程序的入口点。
//
#pragma once
#include "stdafx.h"
#include "Stage.h"
#include "Player.h"
#include "Snowball.h"

IMAGE background_img, title_img, begin_img, game_help_img, move_rule_img;
IMAGE return_img, onemode_img, twomode_img;
int player_cnt = 0;

void ShowMenu()
{
	putimage(0, 0, &background_img);
	putimage(4 * UNIT, UNIT, &title_img);
	putimage(8 * UNIT, 8 * UNIT, &begin_img);
	putimage(8 * UNIT, 10 * UNIT, &game_help_img);
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
	putimage(4 * UNIT, UNIT, &title_img);
	putimage(22 * UNIT, 0, &return_img);
	putimage(10 * UNIT, 9 * UNIT, &onemode_img);
	putimage(10 * UNIT, 11 * UNIT, &twomode_img);
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

extern void LoadMap(Stage &gk);
extern vector<Player> InitPlayer(Stage &gk, int mode);
extern void LoadPlayer(vector<Player> &player);
extern void ControlPlayer(Player &pl, char hit);
extern void SnowBallNewPos(queue<SnowBall> &q);

bool GoGoGo(int level)
{
	Stage gk;
	gk.Init(level);
	vector<Player> player = InitPlayer(gk, player_cnt);
	queue<SnowBall> ball;
	vector<char> hit;
	BeginBatchDraw();
	while (1)
	{
		LoadMap(gk);
		LoadPlayer(player);
		LoadSnowBall(ball);
		FlushBatchDraw();
		//LoadBar();
		//LoadMonster();
		hit = MyKbHit();
		if (hit.size())
		{
			for (int i = 0; i < hit.size(); i++)
			{
				if (hit[i] == 'a' || hit[i] == 'd' || hit[i] == 'j' || hit[i] == 'k')
					ControlPlayer(player[1], hit[i], ball);
				else if (player_cnt == 2)
				{
					if (hit[i] == '<')
						hit[i] = 'a';
					else if (hit[i] == '>')
						hit[i] = 'd';
					else if (hit[i] == '2')
						hit[i] = 'j';
					else if (hit[i] == '3')
						hit[i] = 'k';
					ControlPlayer(player[2], hit[i], ball);
				}
			}
		}
		for (int i = 1; i < player.size(); i++)
			PlayerNewPos(player[i], gk);
		SnowBallNewPos(ball);

		Sleep(10);
	}
	EndBatchDraw();
	return 0;
}

void BeginGame()
{
	int level = 1;
	while (level <= 1) //关卡总数
	{
		if (GoGoGo(level))
		{
			level++;
			continue;
		}
		else
			break;
	}
	if (level == 1) //关卡总数
		; //通关
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
	settextstyle(50, 0, _T("宋体")); //初始化字体
	loadimage(&background_img, _T(".\\img\\background.jpg"));
	loadimage(&title_img, _T(".\\img\\title.bmp"));
	loadimage(&begin_img, _T(".\\img\\begin_game.bmp"));
	loadimage(&game_help_img, _T(".\\img\\game_help.bmp"));
	loadimage(&move_rule_img, _T(".\\img\\move_rule.bmp"));
	loadimage(&return_img, _T(".\\img\\return.jpg"));
	loadimage(&onemode_img, _T(".\\img\\onemode.bmp"));
	loadimage(&twomode_img, _T(".\\img\\twomode.bmp"));
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
		if (ClickOn(click, begin_img, 8 * UNIT, 8 * UNIT))
		{
			ShowMode(); //选择游戏模式
			player_cnt = 0;
			while (1)
			{
				click = GetMouseMsg();
				if (click.mkLButton == true)
				{
					if (ClickOn(click, onemode_img, 10 * UNIT, 9 * UNIT))
						player_cnt = 1;
					else if (ClickOn(click, twomode_img, 10 * UNIT, 11 * UNIT))
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
		else if (ClickOn(click, game_help_img, 8 * UNIT, 10 * UNIT))
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

