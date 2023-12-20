#include <graphics.h>
#include "touwenjian.h"

extern IMAGE ziji1, ziji_d_l, ziji2,ziji_d_r;
extern unsigned int tick;
extern double position_x, position_y;
void show_ziji()
{
	static double tangle;
	tangle = PI / 200 * (tick % 400);
	rotateimage(&ziji_d_l, &ziji2, tangle, WHITE);
	rotateimage(&ziji_d_r, &ziji2, -tangle+PI, WHITE);
	putimage(position_x - 65, position_y-15, &ziji1, NOTSRCERASE);
	putimage(position_x - 65, position_y-15, &ziji_d_l, SRCINVERT);
	putimage(position_x + 35, position_y-15, &ziji1, NOTSRCERASE);
	putimage(position_x + 35, position_y-15, &ziji_d_r, SRCINVERT);
}