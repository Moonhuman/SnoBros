#pragma once
#include "stdafx.h"

class Gift {
public:
	int x, y, px, py, gone, type;
	IMAGE img[2];
	Gift(int k, int a, int b, int pa, int pb)
	{
		type = k;
		gone = 500;
		x = a; y = b;
		px = pa; py = pb;
		wstring path = L".\\img\\gift" + to_wstring(k) + L"-0.png";
		loadimage(&img[0], path.c_str());
		path = L".\\img\\gift" + to_wstring(k) + L"-1.png";
		loadimage(&img[1], path.c_str());
	}
};
void LoadGift(vector<Gift> &gift)
{
	for (int i = 0; i < gift.size(); i++)
	{
		--gift[i].gone;
		if (!gift[i].gone)
		{
			swap(gift[i], gift.back());
			gift.pop_back();
			--i;
		}
		else
		{
			putimage(gift[i].px, gift[i].py, &gift[i].img[0], NOTSRCERASE);
			putimage(gift[i].px, gift[i].py, &gift[i].img[1], SRCINVERT);
		}
	}
}
void NewGift(vector<Gift> &gift, int x, int y, int px, int py)
{
	int rd = rand() % 15;
	if (1 <= rd && rd <= 4)
	{
		gift.push_back(Gift(rd, x, y, px, py));
	}
}