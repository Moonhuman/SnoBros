#pragma once
//#include "stdafx.h"
using namespace std;



class SnowBall {
public:
	IMAGE ball_img;
	int px, py;
	int dstx, dsty;
	SnowBall() 
	{
		loadimage(&ball_img, _T(".\\img\\snowball.bmp"));
	}
};

void LoadSnowBall(queue<SnowBall> &q)
{
	SnowBall front;
	for (int i = 0, end = q.size(); i < end; i++)
	{
		front = q.front();
		q.pop();
		putimage(front.px, front.py, &front.ball_img);
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
				q.push(front);
		}
		else if (front.dstx < front.px)
		{
			front.px -= 5;
			if (front.dstx < front.px)
				q.push(front);
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
		newball.dstx = newball.px + 4 * UNIT;
	}
	else
	{
		newball.px = pl.px - UNIT;
		newball.dsty = newball.py = pl.py;
		newball.dstx = newball.px - 4 * UNIT;
	}
	newball.px = max(newball.px, 0);
	newball.dstx = max(newball.dstx, 0);
	newball.px = min(newball.px, 23 * UNIT);
	newball.dstx = min(newball.dstx, 23 * UNIT);
	q.push(newball);
}