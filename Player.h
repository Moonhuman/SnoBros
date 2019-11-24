#pragma once
#include "stdafx.h"

class Player {
public:
	int x, y, px, py, dx, dy, face, lengque; //face = 0 ³¯×ó£¬ = 1 ³¯ÓÒ
	IMAGE now[2], body[2], left_body[2][2], right_body[2][2], jump_body;
	Player() { dx = dy = face = lengque = 0; }
};

#include "Snowball.h"

void BindImage(Player &p, int k)
{
	loadimage(&p.now[0], _T(".\\img\\now.bmp"));
	
}

vector<Player> InitPlayer(Stage &gk, int mode)
{
	vector<Player> ret(3);
	//Player temp;
	//ret.push_back(temp);
	for (int i = 1; i < 14; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (gk.mp[i][j] == 'A')
			{
				Player alice;
				alice.x = i, alice.y = j;
				alice.px = j * UNIT, alice.py = (i - 1) * UNIT;
				BindImage(alice, 1);
				//ret.push_back(alice);
				ret[1] = alice;
			}
			else if (mode == 2 && gk.mp[i][j] == 'B')
			{
				Player bob;
				bob.x = i, bob.y = j;
				bob.px = j * UNIT, bob.py = (i - 1) * UNIT;
				BindImage(bob, 2);
				//ret.push_back(bob);
				ret[2] = bob;
			}
			if (gk.mp[i][j] == 'A' || gk.mp[i][j] == 'B')
				gk.mp[i][j] = 'O';
		}
	}
	return ret;
}

void LoadPlayer(vector<Player> &player)
{
	for (int i = 1; i < player.size(); i++)
		putimage(player[i].px, player[i].py, &(player[i].now[0]));
}

void ControlPlayer(Player &pl, char hit, queue<SnowBall> &q)
{
	if (hit == 'd' && !pl.dx)
	{
		pl.dx += 10;
		pl.face = 1;
	}
	else if (hit == 'a' && !pl.dx)
	{
		pl.dx -= 10;
		pl.face = 0;
	}
	else if (hit == 'k' && !pl.dy)
		pl.dy -= 100;
	else if (hit == 'j' && !pl.lengque)
	{
		CreateSnowBall(pl, q);
		pl.lengque = 25;
	}
}

void FallDown(Player &pl)
{
	pl.dy += 50;
}

void PlayerNewPos(Player &pl, Stage &gk)
{
	if (pl.lengque)
		pl.lengque--;
	if (!pl.dx && !pl.dy)
		return;
	if (pl.dx > 0)
	{
		pl.px += 2;
		pl.px = min(pl.px, 23 * UNIT);
		pl.dx -= 2;
	}
	else if (pl.dx < 0)
	{
		pl.px -= 2;
		pl.px = max(pl.px, 0);
		pl.dx += 2;
	}
	if (pl.dy < 0)
	{
		pl.py -= 2;
		pl.py = max(pl.py, UNIT);
		pl.dy += 2;
	}
	else if (pl.dy > 0)
	{
		pl.py += 2;
		pl.py = min(pl.py, 12 * UNIT);
		pl.dy -= 2;
	}
	pl.x = (pl.py - 1) / UNIT + 2;
	pl.y = pl.px / UNIT + ((pl.px % UNIT) > 25);
	if (!pl.dy && gk.mp[pl.x + 1][pl.y] != '#')
		FallDown(pl);
	
	/*
	fstream dd; 
	dd.open(".\\dd.txt");
	dd << pl.x << " " << pl.y << endl;
	dd << pl.px << " " << pl.py << endl;
	dd.close();
	*/
}