#include <graphics.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <string.h>
#include "touwenjian.h"
extern int graze,life,sc;
TCHAR hit_num[10];
TCHAR graze_num[10];
TCHAR score_num[15];
TCHAR point_num[10];
TCHAR power_num[10];

extern IMAGE heart0, heart1, heart2, star0, star1, star2;
static int i;
extern int point_, power_;
extern unsigned score_;
void Startup_score()
{
	wcscpy_s(graze_num, _T("0"));
	wcscpy_s(score_num, _T("0"));
	wcscpy_s(point_num, _T("0"));
	wcscpy_s(power_num, _T("0"));
}
void show_score()
{
	void trans_int(int n,TCHAR *str);
	i = 0;
	trans_int(graze, graze_num);
	i = 0;
	trans_int(score_, score_num);
	i = 0;
	trans_int(point_, point_num);
	i = 0;
	trans_int(power_, power_num);
	settextstyle(40, 20, _T("Courier"));
	settextcolor(WHITE);
	outtextxy(830, 90, _T("SCORE"));
	outtextxy(950, 90, score_num);
	outtextxy(830, 290, _T("POINT"));
	outtextxy(950, 290, point_num);
	outtextxy(830, 340, _T("POWER"));
	outtextxy(950, 340, power_num);
	if(power_>=400)
		outtextxy(1050, 340, _T("FULL"));
	outtextxy(830, 390, _T("GRAZE"));
	outtextxy(950, 390, graze_num);
	outtextxy(830, 145, _T("LIFE"));
	outtextxy(830, 195, _T("BOOM"));
	for (i = 1; i <= 10; i++)
	{
		if (i < life)
		{
			putimage(900 + i * 30, 150, &heart2, NOTSRCERASE);
			putimage(900 + i * 30, 150, &heart1, SRCINVERT);
		}
		else
		{
			putimage(900 + i * 30, 150, &heart2, NOTSRCERASE);
			putimage(900 + i * 30, 150, &heart0, SRCINVERT);
		}
		if (i <= sc)
		{
			putimage(900 + i * 30, 200, &star2, NOTSRCERASE);
			putimage(900 + i * 30, 200, &star1, SRCINVERT);
		}
		else
		{
			putimage(900 + i * 30, 200, &star2, NOTSRCERASE);
			putimage(900 + i * 30, 200, &star0, SRCINVERT);
		}
	}
}
void trans_int(int n,TCHAR *str)
{
	if (n == 0) return;
	for (int j = 0; j<i; j++)
		str[i-j] = str[i-j-1];
	str[i+1] = '\0';
	str[0] = n % 10 + '0';
	i++;
	trans_int(n / 10,str);
}