#include "touwenjian.h"
#include <graphics.h>
extern Bullet_* head_;
extern enemy* head_enemy;
extern bullet_enemy* head_be;
void delay(DWORD);
void GameStart()
{
	IMAGE bkground;
	int tick=1;
	char n = 1;
	settextstyle(20, 9, _T("Courier"));
	loadimage(&bkground,_T("material\\lingmeng.png"));
	while (1)
	{
		tick += n;
		if (tick == 1031)
			n = -1;
		if (tick == 0)
			n = 1;
		putimage(0, -tick, &bkground);
		outtextxy(50, 900, _T("press Z to start,X to exit"));
		FlushBatchDraw();
		if ((GetAsyncKeyState(0x58) & 0x8000))
		{
			exit(0);
		}
		if ((GetAsyncKeyState(0x5A) & 0x8000))
		{
			return;
		}
		delay(5);
	}
}
void clearall();
bool GameOver()
{
	clearall();
	char flag=0;
	settextstyle(60, 30, _T("Courier"));
	outtextxy(left_edge+175, 200, _T("GAME OVER"));
	settextstyle(50, 25, _T("Courier"));
	while (1)
	{
		if (flag)
			settextcolor(WHITE);
		else
			settextcolor(0xaaaaff);
		outtextxy(left_edge + 175, 700, _T("restart"));
		if (flag)
			settextcolor(0xaaaaff);
		else
			settextcolor(WHITE);
		outtextxy(left_edge + 175, 780, _T("exit"));
		if ((GetAsyncKeyState(VK_RETURN)|GetAsyncKeyState(0x5A) & 0x8000))
		{
			if (flag == 0)
				return 0;
			else if (flag == 1)
				return 1;
		}
		if ((GetAsyncKeyState(VK_UP)|GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			if (flag)
				flag = 0;
			else
				flag = 1;
		}
		FlushBatchDraw();
		delay(100);
	}
}
void clear_bullet_enemy(bullet_enemy*);
void clear_all_enemy(enemy*);
void clear_fuji_bullet(Bullet_*);
void clearall()
{
	clear_bullet_enemy(head_be);
	clear_all_enemy(head_enemy);
	clear_fuji_bullet(head_);
}