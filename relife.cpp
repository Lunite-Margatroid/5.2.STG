#include "touwenjian.h"
#include <Windows.h>
#include <graphics.h>
extern double position_x, position_y;
void summon_sc();
void delay(DWORD);
bool relife()
{
	setlinecolor(RED);
	setfillcolor(RED);
	fillcircle(position_x, position_y, 7);
	setlinecolor(WHITE);
	circle(position_x, position_y, 80);
	FlushBatchDraw();
	Sleep(200);
	if ((GetAsyncKeyState(0x58) & 0x8000))
	{
		summon_sc();
		return 0;
	}
	return 1;
}