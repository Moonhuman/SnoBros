#pragma once

#include "stdafx.h"

class Monster {
public:
	int x, y, px, py, dx, dy, face, freeze, bigball;
	IMAGE now[2], fzb[5][2];
	IMAGE left[3][2], right[3][2], jump[2][2];
	Monster() { dx = dy = freeze = bigball = face = 0; }
	void InitImage(int k);
};

void Monster::InitImage(int k)
{
	//temp
	loadimage(&now[0], _T(".\\monster\\test.png"));
	loadimage(&now[1], _T(".\\monster\\test1.png"));
	loadimage(&fzb[0][0], _T(".\\img\\bigball0-0.png"));
	loadimage(&fzb[0][1], _T(".\\img\\bigball0-1.png"));
	loadimage(&fzb[1][0], _T(".\\img\\bigball1-0.png"));
	loadimage(&fzb[1][1], _T(".\\img\\bigball1-1.png"));
	loadimage(&fzb[2][0], _T(".\\img\\bigball2-0.png"));
	loadimage(&fzb[2][1], _T(".\\img\\bigball2-1.png"));
	loadimage(&fzb[3][0], _T(".\\img\\bigball3-0.png"));
	loadimage(&fzb[3][1], _T(".\\img\\bigball3-1.png"));
	loadimage(&fzb[4][0], _T(".\\img\\bigball4-0.png"));
	loadimage(&fzb[4][1], _T(".\\img\\bigball4-1.png"));

	wstring path, wsk = to_wstring(k);
	path = L".\\monster\\mon" + wsk + L"le1-0.png";
	loadimage(&left[1][0], path.c_str());
	path = L".\\monster\\mon" + wsk + L"le1-1.png";
	loadimage(&left[1][1], path.c_str());
	path = L".\\monster\\mon" + wsk + L"le2-0.png";
	loadimage(&left[2][0], path.c_str());
	path = L".\\monster\\mon" + wsk + L"le2-1.png";
	loadimage(&left[2][1], path.c_str());
	path = L".\\monster\\mon" + wsk + L"ri1-0.png";
	loadimage(&right[1][0], path.c_str());
	path = L".\\monster\\mon" + wsk + L"ri1-1.png";
	loadimage(&right[1][1], path.c_str());
	path = L".\\monster\\mon" + wsk + L"ri2-0.png";
	loadimage(&right[2][0], path.c_str());
	path = L".\\monster\\mon" + wsk + L"ri2-1.png";
	loadimage(&right[2][1], path.c_str());

	path = L".\\monster\\mon" + wsk + L"jple-0.png";
	loadimage(&jump[0][0], path.c_str());
	path = L".\\monster\\mon" + wsk + L"jple-1.png";
	loadimage(&jump[0][1], path.c_str());
	path = L".\\monster\\mon" + wsk + L"jpri-0.png";
	loadimage(&jump[1][0], path.c_str());
	path = L".\\monster\\mon" + wsk + L"jpri-1.png";
	loadimage(&jump[1][1], path.c_str());
}

vector<Monster> InitMonster(Stage &gk)
{
	vector<Monster> ret;
	for (int i = 1; i < 14; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (gk.mp[i][j] != 'O' && gk.mp[i][j] != '#')
			{
				Monster mon;
				mon.x = i, mon.y = j;
				mon.px = j * UNIT, mon.py = (i - 1) * UNIT;
				mon.InitImage(gk.mp[i][j] - 'D');
				ret.push_back(mon);
				gk.mp[i][j] = 'O';
			}
		}
	}
	return ret;
}

void LoadMonster(vector<Monster> &monster)
{
	for (int i = 0; i < monster.size(); i++)
	{
		if (monster[i].face)
		{
			if (monster[i].dy)
			{
				monster[i].now[0] = monster[i].jump[1][0];
				monster[i].now[1] = monster[i].jump[1][1];
			}
			else
			{
				if ((monster[i].dx / 20) & 1)
				{
					monster[i].now[0] = monster[i].right[1][0];
					monster[i].now[1] = monster[i].right[1][1];
				}
				else
				{
					monster[i].now[0] = monster[i].right[2][0];
					monster[i].now[1] = monster[i].right[2][1];
				}
			}
		}
		else
		{
			if (monster[i].dy)
			{
				monster[i].now[0] = monster[i].jump[0][0];
				monster[i].now[1] = monster[i].jump[0][1];
			}
			else
			{
				if ((monster[i].dx / 20) & 1)
				{
					monster[i].now[0] = monster[i].left[1][0];
					monster[i].now[1] = monster[i].left[1][1];
				}
				else
				{
					monster[i].now[0] = monster[i].left[2][0];
					monster[i].now[1] = monster[i].left[2][1];
				}
			}
		}
		//putimage(monster[i].px, monster[i].py, &monster[i].now[0]);
		putimage(monster[i].px, monster[i].py, &monster[i].now[0], NOTSRCERASE);
		putimage(monster[i].px, monster[i].py, &monster[i].now[1], SRCINVERT);
		if (monster[i].freeze)
		{
			//monster[i].now[0] = monster[i].fzb[(monster[i].freeze - 1) / 100];
			putimage(monster[i].px, monster[i].py, &monster[i].fzb[(monster[i].freeze - 1) / 100][0], NOTSRCERASE);
			putimage(monster[i].px, monster[i].py, &monster[i].fzb[(monster[i].freeze - 1) / 100][1], SRCINVERT);
		}
	}
}

void MFallDown(Monster &monster)
{
	monster.dy += 50;
}

void MonsterNewPos(Monster &monster, Stage &gk)
{
	if (monster.freeze)
		--monster.freeze;
	if (401 <= monster.freeze && monster.freeze  <= 500)
		monster.bigball = 1;
	else
		monster.bigball = 0;
	if (!monster.dx && !monster.dy)
		return;
	if (!monster.freeze)
	{
		if (monster.dx > 0)
		{
			monster.px += 2;
			monster.px = min(monster.px, 22 * UNIT);
			monster.dx -= 2;
		}
		else if (monster.dx < 0)
		{
			monster.px -= 2;
			monster.px = max(monster.px, 0);
			monster.dx += 2;
		}
	}

	if (monster.dy < 0)
	{
		monster.py -= 2;
		monster.py = max(monster.py, UNIT);
		monster.dy += 2;
	}
	else if (monster.dy > 0)
	{
		monster.py += 2;
		monster.py = min(monster.py, 11 * UNIT);
		monster.dy -= 2;
	}

	//x, y;
	monster.x = (monster.py - 1) / UNIT + 2;
	monster.y = monster.px / UNIT + ((monster.px % UNIT) > 25);
	if (!monster.dy && gk.mp[monster.x + 1][monster.y] != '#' && gk.mp[monster.x + 1][monster.y + 1] != '#')
		MFallDown(monster);
}

void GuideMonster(vector<Monster> &monster, Stage &gk)
{
	//fstream dd;
	//dd.open(".\\dd.txt", ios::app);
	

	int bound, op, equ;
	for (int i = 0; i < monster.size(); i++)
	{
		if (monster[i].freeze)
			continue;
		if (!monster[i].dx)
		{
			bound = rand() % 10;
			op = rand() % 10;
			equ = rand() % 2;

			if (equ)
			{
				if (op < bound)
				{
					if (rand() % 5)
						monster[i].dx -= UNIT;
					else
						monster[i].dx -= 2 * UNIT;
					monster[i].face = 0;
				}
				else
				{
					if (rand() % 5)
						monster[i].dx += UNIT;
					else
						monster[i].dx += 2 * UNIT;
					monster[i].face = 1;
				}
			}
			else
			{
				if (op <= bound)
				{
					if (rand() % 5)
						monster[i].dx -= UNIT;
					else
						monster[i].dx -= 2 * UNIT;
					monster[i].face = 0;
				}
				else
				{
					if (rand() % 5)
						monster[i].dx += UNIT;
					else
						monster[i].dx += 2 * UNIT;
					monster[i].face = 1;
				}
			}
		}
		if (!monster[i].dy)
		{
			op = rand() % 500;
			if (!op)
			{
				monster[i].dy -= 2 * UNIT;
			}
		}
		
	}

	//dd.close();
}
extern void NewGift(vector<Gift> &gift, int x, int y, int px, int py);
void KillMonster(vector<Bigball> &bb, vector<Monster> &mon, vector<Gift> &gift)
{
	for (int i = 0; i < bb.size(); i++)
	{
		for (int j = 0; j < mon.size(); j++)
		{
			if (bb[i].x == mon[j].x && bb[i].y == mon[j].y)
			{
				NewGift(gift, mon[j].x, mon[j].y, mon[j].y * UNIT, mon[j].x * UNIT);
				swap(mon[j], mon.back());
				mon.pop_back();
				j--;
			}
		}
	}
}
