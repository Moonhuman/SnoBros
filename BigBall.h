#pragma once
#include "stdafx.h"

class Bigball {
public:
	int x, y, px, py, dx, dy, dir;
	Bigball() { dx = dy = 0; }
	IMAGE img[2];
};

void LoadBigBallImage(Bigball &bb)
{
	loadimage(&bb.img[0], _T(".\\img\\bigball4-0.png"));
	loadimage(&bb.img[1], _T(".\\img\\bigball4-1.png"));
}
void LoadBigball(vector<Bigball> &bb)
{
	for (int i = 0; i < bb.size(); i++)
	{
		putimage(bb[i].px, bb[i].py, &bb[i].img[0], NOTSRCERASE);
		putimage(bb[i].px, bb[i].py, &bb[i].img[1], SRCINVERT);
	}
}
void BFallDown(Bigball &bb)
{
	bb.dy += 50;
}
void ControlBigBall(vector<Bigball> &bb, Stage &gk)
{
	for (int i = 0; i < bb.size(); i++)
	{
		if (!bb[i].dy && gk.mp[bb[i].x + 1][bb[i].y] != '#' && gk.mp[bb[i].x + 1][bb[i].y + 1] != '#')
		{
			BFallDown(bb[i]);
			bb[i].dx = 0;
		}
		if (!bb[i].dx)
		{
			if (bb[i].dir)
			{
				bb[i].dx += 50;
			}
			else
			{
				bb[i].dx -= 50;
			}
		}
	}
}
extern void NewGift(vector<Gift> &gift, int x, int y);
void BigBallNewPos(vector<Bigball> &bb, vector<Gift> &gift)
{
	for (int i = 0; i < bb.size(); i++)
	{
		if (bb[i].dy)
		{
			bb[i].py += 5;
			bb[i].dy -= 5;
		}
		if (bb[i].dx > 0)
		{
			bb[i].px += 5;
			bb[i].dx -= 5;
			if (bb[i].px >= 1100)
			{
				bb[i].px = 1100;
				bb[i].dir = 0;
			}
		}
		else if (bb[i].dx < 0)
		{
			bb[i].px -= 5;
			bb[i].dx += 5;
			if (bb[i].px < 0)
			{
				bb[i].px = 0;
				bb[i].dir = 1;
			}
		}
		bb[i].x = (bb[i].py - 1) / UNIT + 2;
		bb[i].y = bb[i].px / UNIT + ((bb[i].px % UNIT) > 25);
		if ((bb[i].x == 12 && bb[i].px == 0) || (bb[i].x == 12 && bb[i].px == 1100))
		{
			NewGift(gift, bb[i].x, bb[i].y, bb[i].y * UNIT, bb[i].x * UNIT);
			swap(bb[i], bb.back());
			bb.pop_back();
			--i;
		}
	}
}
