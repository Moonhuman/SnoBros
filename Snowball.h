#pragma once
//#include "stdafx.h"
#include "Monster.h"
using namespace std;



class SnowBall {
public:
	IMAGE ball_img[2];
	int x, y;
	int px, py;
	int dstx, dsty;
	SnowBall() 
	{
		loadimage(&ball_img[0], _T(".\\img\\snowball-0.png"));
		loadimage(&ball_img[1], _T(".\\img\\snowball-1.png"));
	}
};

void LoadSnowBall(queue<SnowBall> &q)
{
	SnowBall front;
	for (int i = 0, end = q.size(); i < end; i++)
	{
		front = q.front();
		q.pop();
		putimage(front.px, front.py, &front.ball_img[0], NOTSRCERASE);
		putimage(front.px, front.py, &front.ball_img[1], SRCINVERT);
		q.push(front);
	}
}

void SnowBallNewPos(queue<SnowBall> &q)
{
	SnowBall front;
	for (int i = 0, end = q.size(); i < end; i++)
	{
		front = q.front();
		q.pop();
		if (front.dstx > front.px)
		{
			front.px += 5;
			if (front.dstx > front.px)
			{
				front.x = front.py / UNIT + ((front.py % UNIT) > 25);
				front.y = front.px / UNIT + ((front.px % UNIT) > 25);
				q.push(front);
			}
		}
		else if (front.dstx < front.px)
		{
			front.px -= 5;
			if (front.dstx < front.px)
			{
				front.x = front.py / UNIT + ((front.py % UNIT) > 25);
				front.y = front.px / UNIT + ((front.px % UNIT) > 25);
				q.push(front);
			}
		}
	}
}

void CreateSnowBall(Player &pl, queue<SnowBall> &q)
{
	SnowBall newball;
	if (pl.face)
	{
		newball.px = pl.px + UNIT;
		newball.dsty = newball.py = pl.py;
		newball.dstx = newball.px + 4 * UNIT + pl.shootl * UNIT * 3;
	}
	else
	{
		newball.px = pl.px - UNIT;
		newball.dsty = newball.py = pl.py;
		newball.dstx = newball.px - 4 * UNIT - pl.shootl * UNIT * 3;
	}
	newball.px = max(newball.px, 0);
	newball.dstx = max(newball.dstx, 0);
	newball.px = min(newball.px, 23 * UNIT);
	newball.dstx = min(newball.dstx, 23 * UNIT);
	newball.py = pl.py;
	newball.x = newball.py / UNIT + ((newball.py % UNIT) > 25);
	newball.y = newball.px / UNIT + ((newball.px % UNIT) > 25);
	q.push(newball);
}

void FreezeMonster(queue<SnowBall> &q, vector<Monster> &mon)
{
	SnowBall front;
	for (int i = 0, end = q.size(); i < end; i++)
	{
		front = q.front();
		q.pop();
		int flag = 1;
		for (int j = 0; j < mon.size(); j++)
		{
			if (front.x == mon[j].x && front.y == mon[j].y)
			{
				mon[j].freeze += 100, flag = 0;
				mon[j].freeze = min(mon[j].freeze, 500);
				break;
			}
			else if (front.x == mon[j].x - 1 && front.y == mon[j].y)
			{
				mon[j].freeze += 100, flag = 0;
				mon[j].freeze = min(mon[j].freeze, 500);
				break;
			}	
			else if (front.x == mon[j].x && front.y == mon[j].y + 1)
			{
				mon[j].freeze += 100, flag = 0;
				mon[j].freeze = min(mon[j].freeze, 500);
				break;
			}
			else if (front.x == mon[j].x - 1 && front.y == mon[j].y + 1)
			{
				mon[j].freeze += 100, flag = 0;
				mon[j].freeze = min(mon[j].freeze, 500);
				break;
			}
		}
		if (flag)
		{
			q.push(front);
		}
	}
}