#pragma once
#include "stdafx.h"
class Boss {
public:
	int x, y, px, py, lx, ly, life;
	IMAGE img[2];
	Boss()
	{
		life = 20;
		loadimage(&img[0], _T(".\\monster\\boss-0.png"));
		loadimage(&img[1], _T(".\\monster\\boss-1.png"));
	}
};
void InitBoss(Boss &bs)
{
	bs.x = 3, bs.y = 14;
	bs.px = bs.y * UNIT, bs.py = bs.x * UNIT;
	bs.lx = bs.ly = 10;
}
extern void LoadMap(Stage &gk, vector<Player> &pl);
extern vector<char> MyKbHit();
extern wstring GetLife(int a);
extern IMAGE life_img[2];
void LoadBoss(Boss &bs)
{
	putimage(bs.px, bs.py, &bs.img[0], NOTSRCERASE);
	putimage(bs.px, bs.py, &bs.img[1], SRCINVERT);
	outtextxy(850, 0, _T("Boss:"));
	putimage(1000, 0, &life_img[0], NOTSRCERASE);
	putimage(1000, 0, &life_img[1], SRCINVERT);
	outtextxy(1050, 0, GetLife(bs.life).c_str());
}

void NewMonster(vector<Monster> &mon)
{
	if (rand() % 250 == 0)
	{
		int y = rand() % 12;
		int type = rand() % 4 + 1;
		Monster nm;
		nm.InitImage(type);
		nm.x = 2, nm.y = y;
		nm.px = nm.y * UNIT, nm.py = (nm.x - 1) * UNIT;
		mon.push_back(nm);
	}
}

void SPGuideMonster(vector<Monster> &monster, Stage &gk)
{
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
					if ((monster[i].x / 2) & 1)
						monster[i].dx -= UNIT;
					else
						monster[i].dx -= 2 * UNIT;
					monster[i].face = 0;
				}
				else
				{
					if ((monster[i].x / 2) & 1)
						monster[i].dx += 2 * UNIT;
					else
						monster[i].dx += UNIT;
					monster[i].face = 1;
				}
			}
			else
			{
				if (op <= bound)
				{
					if ((monster[i].x / 2) & 1)
						monster[i].dx -= UNIT;
					else
						monster[i].dx -= 2 * UNIT;
					monster[i].face = 0;
				}
				else
				{
					if ((monster[i].x / 2) & 1)
						monster[i].dx += 2 * UNIT;
					else
						monster[i].dx += UNIT;
					monster[i].face = 1;
				}
			}
		}
	}
}

void SPMonsterNewPos(Monster &monster, Stage &gk)
{
	if (monster.freeze)
		--monster.freeze;
	if (401 <= monster.freeze && monster.freeze <= 500)
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
			monster.px = min(monster.px, 12 * UNIT);
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

	monster.x = (monster.py - 1) / UNIT + 2;
	monster.y = monster.px / UNIT + ((monster.px % UNIT) > 25);
	if (!monster.dy && gk.mp[monster.x + 1][monster.y] != '#' && gk.mp[monster.x + 1][monster.y + 1] != '#')
		monster.dy += 50;
}
void BossKillPlayer(Boss &bs, vector<Player> &pl)
{
	for (int i = 1; i < pl.size(); i++)
	{
		if (pl[i].wudi)
			continue;
		if (bs.x + 2 <= pl[i].x && bs.y + 2 <= pl[i].y)
		{
			if (pl[i].life > 0)
			{
				--pl[i].life;
				pl[i].shootl = 0;
				pl[i].wudi = 200;
				pl[i].px = pl[i].birthpx;
				pl[i].py = pl[i].birthpy;
				pl[i].dx = pl[i].dy = pl[i].face = pl[i].lengque = 0;
				pl[i].x = (pl[i].py - 1) / UNIT + 2;
				pl[i].y = pl[i].px / UNIT + ((pl[i].px % UNIT) > 25);
			}
		}
	}
}

void KillBoss(Boss &bs, vector<Bigball> &bb)
{
	for (int i = 0; i < bb.size(); i++)
	{
		if (bs.x + 2 <= bb[i].x && bs.y + 2 <= bb[i].y)
		{
			--bs.life;
			swap(bb[i], bb.back());
			bb.pop_back();
			--i;
		}
	}
}

bool LastLevel(int life1, int life2, int player_cnt)
{
	Stage gk;
	gk.Init(16);
	vector<Player> player = InitPlayer(gk, player_cnt);
	player[1].life = life1;
	player[2].life = life2;
	Boss bs;
	InitBoss(bs);
	vector<Monster> monster;
	vector<Bigball> bb;
	queue<SnowBall> ball;
	vector<Gift> gift;
	vector<char> hit;
	BeginBatchDraw();

	int ret_cnt = 0;
	while (1)
	{
		LoadMap(gk, player);
		LoadBoss(bs);
		LoadPlayer(player);
		LoadMonster(monster);
		LoadSnowBall(ball);
		LoadGift(gift);
		LoadBigball(bb);
		
		FlushBatchDraw();

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
		SPGuideMonster(monster, gk);
		for (int i = 0; i < monster.size(); i++)
			SPMonsterNewPos(monster[i], gk);
		SnowBallNewPos(ball);

		FreezeMonster(ball, monster);
		KillMonster(bb, monster, gift);
		KillPlayer(monster, player);
		BossKillPlayer(bs, player);
		KillBoss(bs, bb);

		ControlBigBall(bb, gk);
		BigBallNewPos(bb, gift);

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
		if (!bs.life)
		{
			if (ret_cnt == 200)
				break;
			++ret_cnt;
		}

		NewMonster(monster);

		Sleep(10);
	}
	EndBatchDraw();
	return true;
}