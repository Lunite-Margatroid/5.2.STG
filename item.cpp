#include "touwenjian.h"
#include <graphics.h>
#include <math.h>
#include "resource.h"
Item* head_i = NULL, * end_i = NULL;
extern double position_x, position_y;
extern unsigned int score_;
extern int point_, power_;
IMAGE item_p, item_d;
void guide_item(Item*p)
{
	if (p)
	{
		if (p->z)
		{
			p->tangle = atan2(position_y - p->y, position_x - p->x);
			p->v = 10;
		}
		guide_item(p->Pt);
	}
}
void startup_item()
{
	loadimage(&item_d, _T("material\\d.bmp"));
	loadimage(&item_p, _T("material\\P.bmp"));
	//loadimage(&item_d, _T("IMAGE"), _T("d.bmp"));
	//loadimage(&item_p, _T("IMAGE"), MAKEINTRESOURCE(IDB_BITMAP2));
}
void summon_item(double x,double y,int TYPE)
{
	int i = 0;
	while(i++<5)
	if (head_i)
	{
		end_i->Pt = (Item*)malloc(sizeof(Item));
		end_i = end_i->Pt;
		*end_i =
		{
			x+(rand()%100-50),
			y+(rand() % 100 - 50),
			1,
			-5,
			PI / 2,
			TYPE,
			NULL
		};
	}
	else
	{
		head_i = end_i = (Item*)malloc(sizeof(Item));
		*end_i =
		{
			x + (rand() % 100 - 50),
			y + (rand() % 100 - 50),
			1,
			-5,
			PI/2,
			TYPE,
			NULL
		};
	}
}
void catch_item(Item* p)
{
	static double distance;
	if (p)
	{
		if (p->z)
		{
			distance = pow(position_x - p->x, 2) + pow(position_y - p->y, 2);
			if (distance <= 6400)
			{
				p->tangle = atan2(position_y - p->y, position_x - p->x);
				p->v = 10;
			}
			if (distance <= 400)
			{
				p->z = 0;
				if (p->type_item == 1)
				{
					score_ += 100;
					point_ += 1;
				}
				else if(p->type_item==2)
				{
					score_ += 30;
					if(power_<400)
						power_ += 5;
				}
			}
		}
		catch_item(p->Pt);
	}
}
void show_item(Item*p)
{
	if (p)
	{
		if (p->z)
		{
			switch (p->type_item)
			{
			case 1:putimage(p->x - 12, p->y - 12, &item_d); break;
			case 2:putimage(p->x - 12, p->y - 12, &item_p); break;
			default:fillcircle(p->x,p->y,10); break;
			}
		}
		show_item(p->Pt);
	}
}
void free_item()
{
	static Item* T;
	if (head_i&&head_i->y>930)
	{
		T = head_i;
		head_i = head_i->Pt;
		free(T);
	}
	if (head_i && !head_i->z)
	{
		T = head_i;
		head_i = head_i->Pt;
		free(T);
	}
}
void move_item(Item*p)
{
	if (p)
	{
		if (p->z)
		{
			if (p->v <= 5)
			{
				p->v += 0.25;
			}
			p->x += p->v * cos(p->tangle);
			p->y += p->v * sin(p->tangle);
		}
		move_item(p->Pt);
	}
}
void Update_item()
{
	move_item(head_i);
	free_item();
	catch_item(head_i);
	if (position_y < 400)
		guide_item(head_i);
}