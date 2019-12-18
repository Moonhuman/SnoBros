#pragma once
//#include "stdafx.h"

class Player {
public:
	int x, y, px, py, dx, dy, face, lengque, wudi, shootl; //face = 0 ³¯×ó£¬ = 1 ³¯ÓÒ
	int life, birthx, birthy, birthpx, birthpy;
	IMAGE now[2], body[2], shine[2];
	IMAGE left[3][4], right[3][4], jump[2][4];
	Player() { dx = dy = face = lengque = shootl = 0; life = 5; wudi = 200; }
};

#include "Snowball.h"

void BindImage(Player &p, int k)
{
	//loadimage(&p.now[0], _T(".\\img\\test1-0.png"));
	//loadimage(&p.now[1], _T(".\\img\\test1-1.png"));
	if (k == 1)
	{
		loadimage(&p.left[1][0], _T(".\\img\\left1-0.png"));
		loadimage(&p.left[1][1], _T(".\\img\\left1-1.png"));
		loadimage(&p.left[1][2], _T(".\\img\\2left1-0.png"));
		loadimage(&p.left[1][3], _T(".\\img\\2left1-1.png"));
		loadimage(&p.left[2][0], _T(".\\img\\left2-0.png"));
		loadimage(&p.left[2][1], _T(".\\img\\left2-1.png"));
		loadimage(&p.left[2][2], _T(".\\img\\2left2-0.png"));
		loadimage(&p.left[2][3], _T(".\\img\\2left2-1.png"));
		loadimage(&p.right[1][0], _T(".\\img\\right1-0.png"));
		loadimage(&p.right[1][1], _T(".\\img\\right1-1.png"));
		loadimage(&p.right[1][2], _T(".\\img\\2right1-0.png"));
		loadimage(&p.right[1][3], _T(".\\img\\2right1-1.png"));
		loadimage(&p.right[2][0], _T(".\\img\\right2-0.png"));
		loadimage(&p.right[2][1], _T(".\\img\\right2-1.png"));
		loadimage(&p.right[2][2], _T(".\\img\\2right2-0.png"));
		loadimage(&p.right[2][3], _T(".\\img\\2right2-1.png"));
		loadimage(&p.jump[0][0], _T(".\\img\\jple-0.png"));
		loadimage(&p.jump[0][1], _T(".\\img\\jple-1.png"));
		loadimage(&p.jump[0][2], _T(".\\img\\2jple-0.png"));
		loadimage(&p.jump[0][3], _T(".\\img\\2jple-1.png"));
		loadimage(&p.jump[1][0], _T(".\\img\\jpri-0.png"));
		loadimage(&p.jump[1][1], _T(".\\img\\jpri-1.png"));
		loadimage(&p.jump[1][2], _T(".\\img\\2jpri-0.png"));
		loadimage(&p.jump[1][3], _T(".\\img\\2jpri-1.png"));
	}
	else if (k == 2)
	{
		loadimage(&p.left[1][0], _T(".\\img\\2left1-0.png"));
		loadimage(&p.left[1][1], _T(".\\img\\2left1-1.png"));
		loadimage(&p.left[1][2], _T(".\\img\\left1-0.png"));
		loadimage(&p.left[1][3], _T(".\\img\\left1-1.png"));
		loadimage(&p.left[2][0], _T(".\\img\\2left2-0.png"));
		loadimage(&p.left[2][1], _T(".\\img\\2left2-1.png"));
		loadimage(&p.left[2][2], _T(".\\img\\left2-0.png"));
		loadimage(&p.left[2][3], _T(".\\img\\left2-1.png"));
		loadimage(&p.right[1][0], _T(".\\img\\2right1-0.png"));
		loadimage(&p.right[1][1], _T(".\\img\\2right1-1.png"));
		loadimage(&p.right[1][2], _T(".\\img\\right1-0.png"));
		loadimage(&p.right[1][3], _T(".\\img\\right1-1.png"));
		loadimage(&p.right[2][0], _T(".\\img\\2right2-0.png"));
		loadimage(&p.right[2][1], _T(".\\img\\2right2-1.png"));
		loadimage(&p.right[2][2], _T(".\\img\\right2-0.png"));
		loadimage(&p.right[2][3], _T(".\\img\\right2-1.png"));
		loadimage(&p.jump[0][0], _T(".\\img\\2jple-0.png"));
		loadimage(&p.jump[0][1], _T(".\\img\\2jple-1.png"));
		loadimage(&p.jump[0][2], _T(".\\img\\jple-0.png"));
		loadimage(&p.jump[0][3], _T(".\\img\\jple-1.png"));
		loadimage(&p.jump[1][0], _T(".\\img\\2jpri-0.png"));
		loadimage(&p.jump[1][1], _T(".\\img\\2jpri-1.png"));
		loadimage(&p.jump[1][2], _T(".\\img\\jpri-0.png"));
		loadimage(&p.jump[1][3], _T(".\\img\\jpri-1.png"));
	}

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
				alice.birthx = alice.x;
				alice.birthy = alice.y;
				alice.birthpx = alice.px;
				alice.birthpy = alice.py;
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
				bob.birthx = bob.x;
				bob.birthy = bob.y;
				bob.birthpx = bob.px;
				bob.birthpy = bob.py;
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
	{
		if (player[i].life)
		{
			if (player[i].face)
			{
				if (player[i].wudi)
				{
					if (player[i].dy)
					{
						player[i].now[0] = player[i].jump[1][((player[i].wudi / 10) & 1) * 2];
						player[i].now[1] = player[i].jump[1][((player[i].wudi / 10) & 1) * 2 + 1];
					}
					else
					{
						if ((player[i].px / 25) & 1)
						{
							player[i].now[0] = player[i].right[1][((player[i].wudi / 10) & 1) * 2];
							player[i].now[1] = player[i].right[1][((player[i].wudi / 10) & 1) * 2 + 1];
						}
						else
						{
							player[i].now[0] = player[i].right[2][((player[i].wudi / 10) & 1) * 2];
							player[i].now[1] = player[i].right[2][((player[i].wudi / 10) & 1) * 2 + 1];
						}
					}
				}
				else
				{
					if (player[i].dy)
					{
						player[i].now[0] = player[i].jump[1][0];
						player[i].now[1] = player[i].jump[1][1];
					}
					else
					{
						if ((player[i].px / 25) & 1)
						{
							player[i].now[0] = player[i].right[1][0];
							player[i].now[1] = player[i].right[1][1];
						}
						else
						{
							player[i].now[0] = player[i].right[2][0];
							player[i].now[1] = player[i].right[2][1];
						}
					}
				}
			}
			else
			{
				if (player[i].wudi)
				{
					if (player[i].dy)
					{
						player[i].now[0] = player[i].jump[0][((player[i].wudi / 10) & 1) * 2];
						player[i].now[1] = player[i].jump[0][((player[i].wudi / 10) & 1) * 2 + 1];
					}
					else
					{
						if ((player[i].px / 25) & 1)
						{
							player[i].now[0] = player[i].left[1][((player[i].wudi / 10) & 1) * 2];
							player[i].now[1] = player[i].left[1][((player[i].wudi / 10) & 1) * 2 + 1];
						}
						else
						{
							player[i].now[0] = player[i].left[2][((player[i].wudi / 10) & 1) * 2];
							player[i].now[1] = player[i].left[2][((player[i].wudi / 10) & 1) * 2 + 1];
						}
					}
				}
				else
				{
					if (player[i].dy)
					{
						player[i].now[0] = player[i].jump[0][0];
						player[i].now[1] = player[i].jump[0][1];
					}
					else
					{
						if ((player[i].px / 25) & 1)
						{
							player[i].now[0] = player[i].left[1][0];
							player[i].now[1] = player[i].left[1][1];
						}
						else
						{
							player[i].now[0] = player[i].left[2][0];
							player[i].now[1] = player[i].left[2][1];
						}
					}
				}
			}



			//putimage(player[i].px, player[i].py, &(player[i].now[1]));
			putimage(player[i].px, player[i].py, &player[i].now[0], NOTSRCERASE);
			putimage(player[i].px, player[i].py, &player[i].now[1], SRCINVERT);

		}
	}
}
int PushBall(Player &pl, vector<Monster> &mon, vector<Bigball> &bb)
{
	for (int i = 0; i < mon.size(); i++)
	{
		if (mon[i].bigball)
		{
			if (pl.face)
			{
				if (mon[i].y - 1 <= pl.y && pl.y <= mon[i].y)
				{
					if (mon[i].x == pl.x)
					{
						Bigball nb;
						LoadBigBallImage(nb);
						nb.x = mon[i].x;
						nb.y = mon[i].y;
						nb.px = mon[i].px;
						nb.py = mon[i].py;
						nb.dir = 1;
						bb.push_back(nb);
						swap(mon[i], mon.back());
						mon.pop_back();
						return 1;
					}
				}
			}
			else
			{
				if (mon[i].y + 1 <= pl.y && pl.y <= mon[i].y + 2)
				{
					if (mon[i].x == pl.x)
					{
						Bigball nb;
						LoadBigBallImage(nb);
						nb.x = mon[i].x;
						nb.y = mon[i].y;
						nb.px = mon[i].px;
						nb.py = mon[i].py;
						nb.dir = 0;
						bb.push_back(nb);
						swap(mon[i], mon.back());
						mon.pop_back();
						return 1;
					}
				}
			}
		}
	}
	return 0;
}
void ControlPlayer(Player &pl, char hit, queue<SnowBall> &q, vector<Monster> &mon, vector<Bigball> &bb)
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
	{
		pl.dy -= 100;
		pl.dy = max(pl.dy, -pl.py);
	}
	else if (hit == 'j' && !pl.lengque)
	{
		if (PushBall(pl, mon, bb))
			return;
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
	if (pl.wudi)
		pl.wudi--;
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
void KillPlayer(vector<Monster> &mon, vector<Player> &pl)
{
	for (int i = 0; i < mon.size(); i++)
	{
		if (mon[i].freeze)
			continue;
		for (int j = 1; j < pl.size(); j++)
		{
			if (pl[j].wudi)
				continue;
			if ((mon[i].x == pl[j].x && mon[i].y == pl[j].y) || mon[i].x == pl[j].x && mon[i].y + 1 == pl[j].y)
			{
				if (pl[j].life > 0)
				{
					--pl[j].life;
					pl[j].shootl = 0;
					pl[j].wudi = 200;
					pl[j].px = pl[j].birthpx;
					pl[j].py = pl[j].birthpy;
					pl[j].dx = pl[j].dy = pl[j].face = pl[j].lengque = 0;
					pl[j].x = (pl[j].py - 1) / UNIT + 2;
					pl[j].y = pl[j].px / UNIT + ((pl[j].px % UNIT) > 25);
				}
			}
		}
	}
}
void EatGift(Player &pl, vector<Gift> &gift, vector<Monster> &mon)
{
	for (int i = 0; i < gift.size(); i++)
	{
		if (pl.x == gift[i].x && pl.y == gift[i].y)
		{
			if (gift[i].type == 1)
			{
				++pl.life;
			}
			else if (gift[i].type == 2)
			{
				pl.shootl = 1;
			}
			else if (gift[i].type == 3)
			{
				pl.wudi = 500;
			}
			else if (gift[i].type == 4)
			{
				for (int i = 0; i < mon.size(); i++)
				{
					mon[i].freeze += 200;
					mon[i].freeze = min(mon[i].freeze, 500);
				}
			}
			swap(gift[i], gift.back());
			gift.pop_back();
			--i;
		}
	}
}