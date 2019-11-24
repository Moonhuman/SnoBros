#pragma once
#include "stdafx.h"
using namespace std;
class Stage {
public:
	char mp[30][30];
	IMAGE block_img, back_img;
	void Init(int k);
};
void Stage::Init(int k)
{
	wstring path = L".\\stage\\stage"  + to_wstring(k) + L".txt";
	ifstream in;
	in.open(path.c_str());
	if (in.is_open() == false)
	{
		IMAGE ero;
		loadimage(&ero, _T(".\\img\\file_error.bmp"));
		putimage(0, 0, &ero);
		getchar();
		exit(0);
	}
	for (int i = 1; i <= 13; i++)
		in >> mp[i];
	in.close();
	path = L".\\stage\\block" + to_wstring(k) + L".bmp";
	loadimage(&block_img, path.c_str());
	path = L".\\stage\\back" + to_wstring(k) + L".jpg";
	loadimage(&back_img, path.c_str());
}

void LoadMap(Stage &gk)
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
	outtextxy(0, 0, _T("ตฺ1นุ"));
}