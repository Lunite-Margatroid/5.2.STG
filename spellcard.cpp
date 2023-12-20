#include "touwenjian.h"
#include <graphics.h>
#include <math.h>
extern double position_x,position_y;
spellcard* head_sc = NULL;
spellcard* end_sc = NULL;
extern XY x_y;
extern bool exist;
extern enemy* head_enemy;
extern bullet_enemy* head_be;
extern unsigned int imhit,score_;
extern int sc;
void guide_sc(spellcard* p, XY x_y)//导向
{
	if (p)
	{
		if (p->z)
			p->tangle = atan2(x_y.y - p->y, x_y.x - p->x);
		guide_sc(p->Pt, x_y);
	}
}
void move_sc(spellcard* p)//移动&读秒
{
	static unsigned int i;
	if (p)
	{
		p->t--;
		if (head_sc->t == 100)
		{
			p->z = 1;
		}
		if (p->z)
		{
			p->x += 7 * cos(p->tangle)+rand()%9-4;
			p->y += 7 * sin(p->tangle)+rand()%9-4;
		}
		else
		{
			p->x = position_x + 150 * cos(i * PI / 3);
			p->y = position_y + 150 * sin(i * PI / 3);
			i++;
		}
		move_sc(p->Pt);
	}
}
void boom(enemy*, spellcard*);
void build_anime3(spellcard*);
void boom_(bullet_enemy*, spellcard*);
void free_sc()
{
	static spellcard *T;
	if (head_sc && head_sc->t <= 0)
	{
		boom(head_enemy, head_sc);
		boom_(head_be, head_sc);
		build_anime3(head_sc);
		T = head_sc;
		head_sc = head_sc->Pt;
		free(T);
	}
}
void show_sc(spellcard*p)
{
	if (p)
	{
		if (p->z)
		{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillcircle(p->x, p->y, 50);
		}
		show_sc(p->Pt);
	}
}
void build_anime7();
void summon_sc()
{
	imhit = 650;
	sc--;
	for (int i = 0; i < 6; i++)
	{
		if (head_sc)
		{
			end_sc->Pt = (spellcard*)malloc(sizeof(spellcard));
			end_sc = end_sc->Pt;
			*end_sc =
			{
				position_x + 150 * cos(i*PI / 3),
				position_y + 150 * sin(i*PI / 3),
				-PI / 2,
				0,
				60,
				350 + 50 * i,
				NULL
			};
		}
		else
		{
			head_sc = end_sc = (spellcard*)malloc(sizeof(spellcard));
			*end_sc =
			{
				position_x + 150 * cos(i*PI / 3),
				position_y + 150 * sin(i*PI / 3),
				-PI/2,
				0,
				60,
				350+50*i,
				NULL
			};
		}
	}
	build_anime7();
}
void boom(enemy* e, spellcard* s)
{
	static double distance;
	if (e)
	{
		if (e->existing)
		{
			distance = pow(e->x - s->x, 2) + pow(e->y - s->y, 2);
			if (distance <= 40000)
			{
				e->healthpoint -= 300;
				score_ += 300;
			}
		}
		boom(e->Pt,s);
	}
}
void boom_(bullet_enemy*b,spellcard*s)//对敌机子弹
{
	static double distance;
	if (b)
	{
		distance = pow(b->x - s->x, 2) + pow(b->y - s->y, 2);
		if (distance <= 40000)
			b->z = b->g=0;
		boom_(b->Pt, s);
	}
}
void clear_be(bullet_enemy*b,spellcard*s)
{
	static double distance;
	if (s && b)
	{
		distance = pow(b->x - s->x, 2) + pow(b->y - s->y, 2);
		if (distance <= 4000)
			b->z = b->g = 0;
		clear_be(b->Pt, s);
	}
	if (s && !b)
		clear_be(head_be, s->Pt);
}
void clear_BE(bullet_enemy* p);
void Update_spellcard()
{
	free_sc();
	if (exist)
		guide_sc(head_sc,x_y);
	//clear_be(head_be, head_sc);//弹幕太多会溢出
	//clear_BE(head_be);//替换方案
	move_sc(head_sc);
}