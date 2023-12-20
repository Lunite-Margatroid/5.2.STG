#include "touwenjian.h"
#include <graphics.h>
#include <math.h>

bullet_enemy* head_be = NULL;
bullet_enemy *end_be = NULL;
IMAGE b1e1, b1e2;

DynamicMemory dmEnemyBullet(sizeof(bullet_enemy));

extern double position_x;
extern double position_y;
extern int graze,life,sc;
extern unsigned int tick;
extern unsigned int imhit;
extern int power_;
void show_be_fun(bullet_enemy* p)
{
	if (p)
	{
		if (p->z)
			switch (p->shape)
			{
			case 1:
				setlinestyle(PS_SOLID, 5);
				setlinecolor(RGB(0, 0, 255));
				setfillcolor(WHITE);
				fillcircle((int)(p->x + 0.5), (int)(p->y + 0.5), p->r);
				break;
			case 2:
				setlinestyle(PS_SOLID, 5);
				setlinecolor(RGB(255, 0, 0));
				setfillcolor(WHITE);
				fillcircle((int)(p->x + 0.5), (int)(p->y + 0.5), p->r);
				break;
			case 3:
				setlinestyle(PS_SOLID, 5);
				setlinecolor(RGB(0, 255, 0));
				setfillcolor(WHITE);
				fillcircle((int)(p->x + 0.5), (int)(p->y + 0.5), p->r);
				break;
			case 4:
				setlinestyle(PS_SOLID, 1);
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillcircle((int)(p->x + 0.5), (int)(p->y + 0.5), p->r);
				break;
			default:
				setlinestyle(PS_SOLID, 5);
				setlinecolor(RGB(0, 0, 255));
				setfillstyle(BS_SOLID);
				setfillcolor(WHITE); 
				fillcircle((int)(p->x + 0.5), (int)(p->y + 0.5), p->r);
				break;
			}
		show_be_fun(p->Pt);
	}
}
void show_be()
{
	show_be_fun(head_be);
}
void Update_be(bullet_enemy*p)
{
	if (p)
	{
		p->x += p->vx;
		p->y += p->vy;
		p->t--;
		Update_be(p->Pt);
	}
}
void Free_be()
{
	if (head_be && (head_be->t <= 0))
	{
		bullet_enemy* t = head_be;
		head_be = head_be->Pt;
		//free(t);
		dmEnemyBullet.MyFree();
	}

}
void summon_be1(enemy* p)//1.不停锁定自机
{
	static double tangle;
	if (p->t % 70 == 0)
	{
		tangle = atan2(position_y - p->y, position_x - p->x);
		if (head_be == NULL)
		{
			//head_be = end_be = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			head_be = end_be = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->t = 100;
			end_be->r = 15;
			end_be->vx = 10 * cos(tangle);
			end_be->vy = 10 * sin(tangle);
			end_be->Pt = NULL;
		}
		else
		{
			//end_be->Pt = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			end_be->Pt = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be = end_be->Pt;
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->r = 15;
			end_be->t = 100;
			end_be->vx = 10 * cos(tangle);
			end_be->vy = 10 * sin(tangle);
			end_be->Pt = NULL;
		}
	}
}
void summon_be2(enemy* p)//2.锁定自机十连
{
	static double tangle;
	if (tick+p->T<102&&tick%10==0)
	{
		tangle = atan2(position_y - p->y, position_x - p->x);
		if (head_be == NULL)
		{
			//head_be = end_be = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			head_be = end_be = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->t = 100;
			end_be->r = 15;
			end_be->shape = 2;
			end_be->vx = 10 * cos(tangle);
			end_be->vy = 10 * sin(tangle);
			end_be->Pt = NULL;
		}
		else
		{
			//end_be->Pt = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			end_be->Pt = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be = end_be->Pt;
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->r = 15;
			end_be->shape = 2;
			end_be->t = 100;
			end_be->vx = 10 * cos(tangle);
			end_be->vy = 10 * sin(tangle);
			end_be->Pt = NULL;
		}
	}
}
void summon_be3(enemy* p)//3.锁定自机12方向十连
{
	static double tangle;
	static int i;
	if (tick+p->T <= 201 && tick % 10 == 0)
	{
		tangle = atan2(position_y - p->y, position_x - p->x);
		i = 0;
		if (head_be == NULL)
		{
			//head_be = end_be = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			head_be = end_be = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->t = 100;
			end_be->r = 15;
			end_be->shape = 3;
			end_be->vx = 10 * cos(tangle);
			end_be->vy = 10 * sin(tangle);
			end_be->Pt = NULL;
			i++;
		}
		else
		{
			for (; i < 12; i++)
			{
				//end_be->Pt = (bullet_enemy*)malloc(sizeof(bullet_enemy));
				end_be->Pt = (bullet_enemy*)dmEnemyBullet.MyMalloc();
				end_be = end_be->Pt;
				end_be->x = p->x;
				end_be->y = p->y;
				end_be->z = 1;
				end_be->g = 1;
				end_be->r = 15;
				end_be->shape = 3;
				end_be->t = 100;
				end_be->vx = 10 * cos(tangle+i*PI/6);
				end_be->vy = 10 * sin(tangle+i*PI/6);
				end_be->Pt = NULL;
			}
		}
	}
}
double build_anime8(enemy* p);
void summon_be4(enemy* p)//4.beem
{
	static double tangle;
	static int i;
	if(-p->T + 250 == tick)
		 tangle=build_anime8(p);
	if (-p->T + 300 == tick)
	{
		for (i = 0; i < 150; i++)
		{
			if (head_be)
			{
				//end_be->Pt = (bullet_enemy*)malloc(sizeof(bullet_enemy));
				end_be->Pt = (bullet_enemy*)dmEnemyBullet.MyMalloc();
				end_be = end_be->Pt;
				*end_be =
				{
					p->x + i * 10 * cos(tangle),
					p->y + i * 10 * sin(tangle),
					1,
					1,
					0,
					0,
					15,
					100,
					4,
					NULL
				};
			}
			else
			{
				//head_be = end_be = (bullet_enemy*)malloc(sizeof(bullet_enemy));
				head_be = end_be = (bullet_enemy*)dmEnemyBullet.MyMalloc();
				*end_be =
				{
					p->x + i * 10 * cos(tangle),
					p->y + i * 10 * sin(tangle),
					1,
					1,
					0,
					0,
					15,
					100,
					4,
					NULL
				};
			}
		}
	}
}
void summon_be5(enemy* p)//5.不停锁定自机slow
{
	static double tangle;
	if (p->t % 70 == 0)
	{
		tangle = atan2(position_y - p->y, position_x - p->x);
		if (head_be == NULL)
		{
			//head_be = end_be = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			head_be = end_be = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->t = 300;
			end_be->r = 15;
			end_be->vx = 5 * cos(tangle);
			end_be->vy = 5 * sin(tangle);
			end_be->Pt = NULL;
		}
		else
		{
			//end_be->Pt = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			end_be->Pt = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be = end_be->Pt;
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->r = 15;
			end_be->t = 300;
			end_be->vx = 5 * cos(tangle);
			end_be->vy = 5 * sin(tangle);
			end_be->Pt = NULL;
		}
	}
}
void summon_be6(enemy* p)//6.锁定自机十连slow
{
	static double tangle;
	if (tick + p->T < 102 && tick % 10 == 0)
	{
		tangle = atan2(position_y - p->y, position_x - p->x);
		if (head_be == NULL)
		{
			//head_be = end_be = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			head_be = end_be = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->t = 300;
			end_be->r = 15;
			end_be->shape = 2;
			end_be->vx = 5 * cos(tangle);
			end_be->vy = 5 * sin(tangle);
			end_be->Pt = NULL;
		}
		else
		{
			//end_be->Pt = (bullet_enemy*)malloc(sizeof(bullet_enemy));
			end_be->Pt = (bullet_enemy*)dmEnemyBullet.MyMalloc();
			end_be = end_be->Pt;
			end_be->x = p->x;
			end_be->y = p->y;
			end_be->z = 1;
			end_be->g = 1;
			end_be->r = 15;
			end_be->shape = 2;
			end_be->t = 300;
			end_be->vx = 5 * cos(tangle);
			end_be->vy = 5 * sin(tangle);
			end_be->Pt = NULL;
		}
	}
}
void summon_be(enemy*p)
{
	if (p)
	{
	if (p->existing)
		switch (p->shot)
		{
		case 0:break;
		case 1:summon_be1(p); break;
		case 2:summon_be2(p); break;
		case 3:summon_be3(p); break;
		case 4:summon_be4(p); break;
		case 5:summon_be5(p); break;
		case 6:summon_be6(p); break;
		default:summon_be4(p); break;
		}
	summon_be(p->Pt);
	}
}
void clear_bullet_enemy(bullet_enemy*p)
{
	static bullet_enemy* T;
	if (p)
	{
		T = head_be;
		head_be = head_be->Pt;
		//free(T);
		dmEnemyBullet.MyFree();
		clear_bullet_enemy(head_be);
	}
}
bool relife();
void build_anime6(bullet_enemy*);
void build_anime4();
void hit_ziji(bullet_enemy*p)
{
	if (p)
	{
		double distance2 = pow(p->x - position_x, 2) + pow(p->y - position_y, 2);
		if (imhit==0&&distance2 <= pow(p->r + 7.0, 2) && p->z)
		{
			if (relife())
			{
				clear_bullet_enemy(head_be);
				build_anime4();
				imhit = 400;
				life--;
				power_ /= 2;
				sc = 3;
				p->z = 0;
				return;
			}
		}
		if (distance2 <= pow(p->r + 40.0, 2) && p->g )
		{
			graze++;
			p->g = false;
			build_anime6(p);
		}
		hit_ziji(p->Pt);
	}
}