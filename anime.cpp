#include "touwenjian.h"
#include <graphics.h>
#include <math.h>
anime* head_anm = NULL;
anime* end_anm = NULL;

DynamicMemory dmAnime1(sizeof(anime));
DynamicMemory dmAnime2(sizeof(anime));

extern double position_x, position_y;
extern bool position_z;
extern bullet_enemy* head_be;
void clear_BE(bullet_enemy* p)
{
	static double distance;
	if (p)
	{
		if (p->z)
		{
			distance = pow(position_x - p->x, 2) + pow(position_y - p->y, 2);
			if (distance <= 40000)
				p->z = p->g = 0;
		}
		clear_BE(p->Pt);
	}
}
void build_anime1(Bullet* p)
{
	static int randx, randy;
	randx = rand() % 10 - 5;
	randy = rand() % 10 - 5;
	if (head_anm)
	{
		//end_anm->Pt = (anime*)malloc(sizeof(anime));
		end_anm->Pt = (anime*)dmAnime1.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			p->x+randx,
			p->y+randy,
			1,
			15,
			NULL
		};
	}
	else
	{
		//head_anm = end_anm = (anime*)malloc(sizeof(anime));
		head_anm = end_anm = (anime*)dmAnime1.MyMalloc();
		*head_anm =
		{
			p->x+randx,
			p->y+randy,
			1,
			15,
			NULL
		};
	}
}
void build_anime2(Bullet_* p)
{
	if (head_anm)
	{
		//end_anm->Pt = (anime*)malloc(sizeof(anime));
		end_anm->Pt = (anime*)dmAnime2.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			p->x,
			p->y,
			2,
			10,
			NULL
		};
	}
	else
	{
		//head_anm = end_anm = (anime*)malloc(sizeof(anime));
		head_anm = end_anm = (anime*)dmAnime2.MyMalloc();
		*head_anm =
		{
			p->x,
			p->y,
			2,
			10,
			NULL
		};
	}
}
void build_anime3(spellcard * p)
{
	if (head_anm)
	{
		end_anm->Pt = (anime*)malloc(sizeof(anime));
		//end_anm->Pt = (anime*)dmAnime.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			p->x,
			p->y,
			3,
			20,
			NULL
		};
	}
	else
	{
		head_anm = end_anm = (anime*)malloc(sizeof(anime));
		//head_anm = end_anm = (anime*)dmAnime.MyMalloc();
		*head_anm =
		{
			p->x,
			p->y,
			3,
			20,
			NULL
		};
	}
}
void build_anime4()
{
	if (head_anm)
	{
		end_anm->Pt = (anime*)malloc(sizeof(anime));
		//end_anm->Pt = (anime*)dmAnime.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			position_x,
			position_y,
			4,
			180,
			NULL
		};
	}
	else
	{
		head_anm = end_anm = (anime*)malloc(sizeof(anime));
		//head_anm = end_anm = (anime*)dmAnime.MyMalloc();
		*head_anm =
		{
			position_x,
			position_y,
			4,
			180,
			NULL
		};
	}
}
void build_anime5(enemy* p)
{
	if (head_anm)
	{
		end_anm->Pt = (anime*)malloc(sizeof(anime));
		//end_anm->Pt = (anime*)dmAnime.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			p->x,
			p->y,
			5,
			40,
			NULL,
			rand()%12*PI/6
		};
	}
	else
	{
		head_anm = end_anm = (anime*)malloc(sizeof(anime));
		//head_anm = end_anm = (anime*)dmAnime.MyMalloc();
		*head_anm =
		{
			p->x,
			p->y,
			5,
			40,
			NULL,
			rand() % 12 * PI / 6
		};
	}
}
void build_anime6(bullet_enemy* p)
{
	if (head_anm)
	{
		end_anm->Pt = (anime*)malloc(sizeof(anime));
		//end_anm->Pt = (anime*)dmAnime.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			p->x,
			p->y,
			6,
			15,
			NULL,
			(rand()%360)*PI/18
		};
	}
	else
	{
		head_anm = end_anm = (anime*)malloc(sizeof(anime));
		//head_anm = end_anm = (anime*)dmAnime.MyMalloc();
		*head_anm =
		{
			p->x,
			p->y,
			6,
			15,
			NULL,
			(rand() % 360)* PI / 18
		};
	}
}
void build_anime7()
{
	if (head_anm)
	{
		end_anm->Pt = (anime*)malloc(sizeof(anime));
		//end_anm->Pt = (anime*)dmAnime.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			position_x,
			position_y,
			7,
			250,
			NULL
		};
	}
	else
	{
		head_anm = end_anm = (anime*)malloc(sizeof(anime));
		//head_anm = end_anm = (anime*)dmAnime.MyMalloc();
		*head_anm =
		{
			position_x,
			position_y,
			7,
			250,
			NULL
		};
	}
}
double build_anime8(enemy*p)
{
	if(head_anm)
	{
		end_anm->Pt = (anime*)malloc(sizeof(anime));
		//end_anm->Pt = (anime*)dmAnime.MyMalloc();
		end_anm = end_anm->Pt;
		*end_anm =
		{
			p->x,
			p->y,
			8,
			50,
			NULL,
			atan2(position_y - p->y,position_x - p->x)
		};
	}
	else
	{
		head_anm = end_anm = (anime*)malloc(sizeof(anime));
		//head_anm = end_anm = (anime*)dmAnime.MyMalloc();
		*head_anm =
		{
			p->x,
			p->y,
			8,
			50,
			NULL,
			atan2(position_y - p->y,position_x - p->x)
		};
	}
	return atan2(position_y - p->y, position_x - p->x);
}
void free_anime1()
{
	static anime* T;
	if (head_anm->t<=0)
	{
		T = head_anm;
		head_anm = head_anm->Pt;
		//free(T);
		dmAnime1.MyFree();
	}
}
void free_anime2(anime*p)
{
	static anime* T;
	if(p)
	if (p->Pt)
	{
		if (p->Pt->t <= 0)
		{
			T = p->Pt;
			p->Pt = p->Pt->Pt;
			//free(T);
			dmAnime2.MyFree();
		}
		free_anime2(p->Pt);
	}
}
void free_anime()
{
	if (head_anm)
	{
		free_anime2(head_anm);
		free_anime1();
	}
}
void anime1(anime*p)//自机子弹
{
	setlinecolor(0x8888ff);
	setlinestyle(PS_SOLID, 3);
	rectangle((int)(p->x+0.5)-20+p->t,(int)(p->y+0.5)-20+p->t,(int)(p->x+0.5)+20-p->t,(int)(p->y+0.5)+20-p->t);
	p->t--;
}
void anime2(anime* p)//子机子弹
{
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 3);
	circle((int)(p->x + 0.5), (int)(p->y + 0.5), 25-p->t);
	p->t--;
}
void anime3(anime* p)//符卡BOOM
{
	setlinestyle(PS_SOLID, 5);
	setlinecolor(WHITE);
	circle(p->x, p->y, 210);
	setfillcolor(0xDDDDFF);
	fillcircle(p->x, p->y, 200 - p->t*6);
	setfillcolor(0xAAAAFF);
	fillcircle(p->x, p->y, 170 - p->t * 6);
	setfillcolor(0x6666FF);
	fillcircle(p->x, p->y, 150 - p->t * 4);
	/*setfillcolor(RED);
	setlinecolor(WHITE);
	static unsigned char i;
	static double tangle;
	static double d;
	for (i = 0; i < 6; i++)
	{
		d = 200 - 4 * p->t;
		tangle = PI * p->t / 24+i*PI/3;
		fillcircle((int)(p->x + d * cos(tangle) + 0.5), (int)(p->y + d * sin(tangle) + 0.5), 15);
		fillcircle((int)(p->x + d * cos(tangle + PI / 6) + 0.5), (int)(p->y + d * sin(tangle + PI / 6) + 0.5), 15);
	}*/
	p->t--;
}

void anime4(anime* p)//自机
{
	if (p->t > 100)
	{
		position_z = 0;
		setlinestyle(PS_SOLID, p->t / 10);
		setlinecolor(WHITE);
		circle(position_x, position_y, 630 - p->t * 3);
		circle(position_x, position_y, 1280 - p->t * 6);
	}
	else
	{
		clear_BE(head_be);
		position_z = 1;
		position_x = 450;
		position_y = 830 + p->t;
	}
	p->t--;
}
void anime5(anime* p)//敌机
{
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, p->t/10);
	static double d;
	d = 0.05*(1600 - p->t * p->t);
	circle(p->x+d*cos(p->tangle), p->y+d*sin(p->tangle), p->t/2);
	circle(p->x + 0.5*d * cos(p->tangle+1), p->y + 0.5*d * sin(p->tangle+1), p->t/2);
	circle(p->x + 0.7*d * cos(p->tangle+2), p->y + 0.7*d * sin(p->tangle+2), p->t/2);
	circle(p->x + 0.4*d * cos(p->tangle+3), p->y + 0.2*d * sin(p->tangle+3), p->t/2);
	circle(p->x + 0.6*d * cos(p->tangle+4), p->y + 0.6*d * sin(p->tangle+4), p->t/2);
	circle(p->x + d * cos(p->tangle+5), p->y + d * sin(p->tangle+5), p->t/2);
	p->t--;
}
void anime6(anime* p)//擦弹
{
	setlinestyle(PS_SOLID, 1);
	setlinecolor(0xffffff);
	setfillcolor(0x5555ff);
	fillcircle((int)((position_x+p->x)/2)+(15-p->t)*cos(p->tangle), (int)((position_y+p->y)/2) + (15 - p->t) * sin(p->tangle), 3);
	p->t--;
}
void anime7(anime* p)//符卡SHOT
{
	
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	clear_BE(head_be);
	static double tangle;
	if (p->t > 200)
	{
		fillcircle(position_x + 150 * cos(0)+rand()%5-2, position_y + 150 * sin(0) + rand() % 5 - 2, 260 - p->t);
		fillcircle(position_x + 150 * cos(PI / 3) + rand() % 5 - 2, position_y + 150 * sin(PI / 3) + rand() % 5 - 2, 260 - p->t);
		fillcircle(position_x + 150 * cos(PI / 3 * 2) + rand() % 5 - 2, position_y + 150 * sin(PI / 3 * 2) + rand() % 5 - 2, 260 - p->t);
		fillcircle(position_x + 150 * cos(-PI / 3) + rand() % 5 - 2, position_y + 150 * sin(-PI / 3) + rand() % 5 - 2, 260 - p->t);
		fillcircle(position_x + 150 * cos(-PI / 3 * 2) + rand() % 5 - 2, position_y + 150 * sin(-PI / 3 * 2) + rand() % 5 - 2, 260 - p->t);
		fillcircle(position_x + 150 * cos(PI) + rand() % 5 - 2, position_y + 150 * sin(PI) + rand() % 5 - 2, 260 - p->t);
	}
	else
	{
		tangle = PI * p->t / 200;
		fillcircle(position_x + 150 * cos(tangle) + rand() % 5 - 2, position_y + 150 * sin(tangle) + rand() % 5 - 2, 60);
		fillcircle(position_x + 150 * cos(PI / 3 + tangle) + rand() % 5 - 2, position_y + 150 * sin(PI / 3 + tangle) + rand() % 5 - 2, 60);
		fillcircle(position_x + 150 * cos(PI / 3 * 2 + tangle) + rand() % 5 - 2, position_y + 150 * sin(PI / 3 * 2 + tangle) + rand() % 5 - 2, 60);
		fillcircle(position_x + 150 * cos(-PI / 3 + tangle) + rand() % 5 - 2, position_y + 150 * sin(-PI / 3 + tangle) + rand() % 5 - 2, 60);
		fillcircle(position_x + 150 * cos(-PI / 3 * 2 + tangle) + rand() % 5 - 2, position_y + 150 * sin(-PI / 3 * 2 + tangle) + rand() % 5 - 2, 60);
		fillcircle(position_x + 150 * cos(PI + tangle) + rand() % 5 - 2, position_y + 150 * sin(PI + tangle) + rand() % 5 - 2, 60);
	}
	p->t--;
}
void anime8(anime* p)
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(WHITE);
	line(p->x, p->y, p->x + 1500 * cos(p->tangle), 1500 * sin(p->tangle));
	p->t--;
}

void show_anime(anime*p)
{
	if (p)
	{
		switch (p->type_anime)
		{
		case 1:anime1(p); break;
		case 2:anime2(p); break;
		case 3:anime3(p); break;
		case 4:anime4(p); break;
		case 5:anime5(p); break;
		case 6:anime6(p); break;
		case 7:anime7(p); break;
		case 8:anime8(p); break;
		default: break;
		}
		show_anime(p->Pt);
	}
}