#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include "touwenjian.h"
extern unsigned int tick,score_;
enemy *head_enemy=NULL;
enemy* end_enemy = NULL;
IMAGE enemy1, enemy1m;
IMAGE enemy101, enemy101m;
IMAGE enemy2, enemy2m;
IMAGE enemy201, enemy201m;
IMAGE enemy3_1, enemy3_1m, enemy3_2, enemy3_2m;
IMAGE enemy4_1, enemy4_1m, enemy4_2, enemy4_2m;

void EnemyMoveFunction1(enemy* p)//1.横向向右移动 1xs/t
{
	p->x += 1;
}
void EnemyMoveFunction2(enemy* p)//2.200t变速向下450xs 向右1.5xs/t
{
	if (tick+p->T <= 200)
		p->y += (-0.0225 * (p->T+tick) + 4.5);
	else
		p->x += 1.5;
}
void EnemyMoveFunction3(enemy* p)//3.200t变速向下450xs 向左1.5xs/t
{
	if (tick+p->T <= 200)
		p->y += (-0.0225 * (tick+p->T) + 4.5);
	else
		p->x -= 1.5;
}
void EnemyMoveFunction4(enemy* p)//4.横向向左移动 1xs/t
{
	p->x -= 1;
}
void EnemyMoveFunction5(enemy* p)//5.右上 5xs/t
{
	p->x += 5;
	p->y -= 5;
}
void EnemyMoveFunction6(enemy* p)//6.左上 5xs/t
{
	p->x -= 5;
	p->y -= 5;
}

void LoadEnemyImage()
{
	loadimage(&enemy1, _T("material\\enemy1.png"));
	loadimage(&enemy1m, _T("material\\enemy1m.png"));
	loadimage(&enemy2, _T("material\\enemy2.png"));
	loadimage(&enemy2m, _T("material\\enemy2m.png"));
	loadimage(&enemy101, _T("material\\enemy101.png"));
	loadimage(&enemy101m, _T("material\\enemy101m.png"));
	loadimage(&enemy201, _T("material\\enemy201.png"));
	loadimage(&enemy201m, _T("material\\enemy201m.png"));
	loadimage(&enemy3_1, _T("material\\enemy3_1.png"));
	loadimage(&enemy3_1m, _T("material\\enemy3_1m.png"));
	loadimage(&enemy3_2, _T("material\\enemy3_2.png"));
	loadimage(&enemy3_2m, _T("material\\enemy3_2m.png"));
	loadimage(&enemy4_1, _T("material\\enemy4_1.png"));
	loadimage(&enemy4_1m, _T("material\\enemy4_1m.png"));
	loadimage(&enemy4_2, _T("material\\enemy4_2.png"));
	loadimage(&enemy4_2m, _T("material\\enemy4_2m.png"));
}
/*void Summon_Enemy()
{
	static int i = 0;
	if (++i < 10)
	{
		end_enemy->Pt = (enemy*)malloc(sizeof(enemy));
		end_enemy = end_enemy->Pt;
		end_enemy->x = left_edge;
		end_enemy->y = 100;
		end_enemy->t = 800;
		end_enemy->T = -110*i;
		end_enemy->healthpoint = 200;
		end_enemy->r = 25;
		end_enemy->shot = 2;
		end_enemy->existing = 0;
		end_enemy->Pt = NULL;
		Summon_Enemy();
	}
}
void Summon_head()
{
	head_enemy = end_enemy = (enemy*)malloc(sizeof(enemy));
	head_enemy->x = left_edge;
	head_enemy->y = 100;
	head_enemy->t = 800;
	head_enemy->T = 0;
	head_enemy->healthpoint = 200;
	head_enemy->r = 25;
	head_enemy->shot = 2;
	head_enemy->existing = 0;
	head_enemy->Pt = NULL;
	Summon_Enemy();
}*/

void Summon_head()
{
	FILE* fp;
	int i,n;
	errno_t err;
	if((err=fopen_s(&fp,"data\\data.dat", "rb"))!=0)
	//if((fp=fopen("test.dat","rb"))==NULL)
		exit(0);
	fread(&n, sizeof(int), 1, fp);
	head_enemy = end_enemy = (enemy*)malloc(sizeof(enemy));
	fread(head_enemy, sizeof(enemy), 1, fp);
	for (i = 1; i < n; i++)
	{
		end_enemy->Pt = (enemy*)malloc(sizeof(enemy));
		end_enemy = end_enemy->Pt;
		fread(end_enemy, sizeof(enemy), 1, fp);
	}
	fclose(fp);
}
void summon_item(double,double,int);
void build_anime5(enemy*);
void Update_Enemy(enemy* p)//运动，0血清理，越界=0
{
	if (p)
	{
		if(-p->T==tick)
			p->existing = 1;
		if (-p->T<=tick)
			p->t--;
		if (p->existing && p->healthpoint <= 0)
		{
			summon_item(p->x, p->y, rand() % 2 + 1);
			build_anime5(p);
		}
		if (p->healthpoint <= 0||p->x+50<left_edge|| p->y + 50 < top_edge|| p->x - 50 > right_edge||p->y-50>bottom_edge)
			p->existing = 0;
		if (p->existing)
			switch (p->moving)
			{
			case 0:break;
			case 1:EnemyMoveFunction1(p); break;
			case 2:EnemyMoveFunction2(p); break;
			case 3:EnemyMoveFunction3(p); break;
			case 4:EnemyMoveFunction4(p); break;
			case 5:EnemyMoveFunction5(p); break;
			case 6:EnemyMoveFunction6(p); break;
			default:EnemyMoveFunction1(p); break;
			}
		Update_Enemy(p->Pt);
	}
}
void Free_enemy()
{
	if (head_enemy && head_enemy->t <= 0)
	{
		enemy* enemy_t = head_enemy;
		head_enemy = head_enemy->Pt;
		free(enemy_t);
	}
}
void build_anime1(Bullet*);
void hit_enemy(Bullet*b,enemy*e)//自机子弹击中判定
{
	if (b && e)
	{
		if (b->z && e->existing)
		{
			double distance2 = pow(b->x - e->x, 2) + pow(b->y-e->y,2);
			if ((int)(distance2 + 0.5) <= (e->r + 10) * (e->r + 10))
			{
				e->healthpoint -= 20;
				score_ += 20;
				b->z = 0;
				build_anime1(b);
			}
		}
		hit_enemy(b, e->Pt);
	}
	if (b && !e)
		hit_enemy(b->Pt, head_enemy);
}

void show_enemy(enemy* p)
{
	if (p)
	{
		if (p->existing)
			switch (p->type_enemy)
			{
			case 1:
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 25 + 0.5), &enemy1m, NOTSRCERASE);
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 25 + 0.5), &enemy1, SRCINVERT);
				break;
			case 2:
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 30 + 0.5), &enemy2m, NOTSRCERASE);
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 30 + 0.5), &enemy2, SRCINVERT);
				break;
			case 101:
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 25 + 0.5), &enemy101m, NOTSRCERASE);
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 25 + 0.5), &enemy101, SRCINVERT);
				break;
			case 201:
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 30 + 0.5), &enemy201m, NOTSRCERASE);
				putimage((int)(p->x - 25 + 0.5), (int)(p->y - 30 + 0.5), &enemy201, SRCINVERT);
				break;
			case 3:
				if (tick / 10 % 2)
				{
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_1m, NOTSRCERASE);
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_1, SRCINVERT);
				}
				else
				{
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_2m, NOTSRCERASE);
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_2, SRCINVERT);
				}
				break;
			case 4:
				if (tick / 10 % 2)
				{
					putimage((int)(p->x - 35 + 0.5), (int)(p->y - 35 + 0.5), &enemy4_1m, NOTSRCERASE);
					putimage((int)(p->x - 35 + 0.5), (int)(p->y - 35 + 0.5), &enemy4_1, SRCINVERT);
				}
				else
				{
					putimage((int)(p->x - 35 + 0.5), (int)(p->y - 35 + 0.5), &enemy4_2m, NOTSRCERASE);
					putimage((int)(p->x - 35 + 0.5), (int)(p->y - 35 + 0.5), &enemy4_2, SRCINVERT);
				}
				break;
			default:
				if (tick / 10 % 2)
				{
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_1m, NOTSRCERASE);
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_1, SRCINVERT);
				}
				else
				{
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_2m, NOTSRCERASE);
					putimage((int)(p->x - 30 + 0.5), (int)(p->y - 10 + 0.5), &enemy3_2, SRCINVERT);
				}
				break;
			}
		show_enemy(p->Pt);
	}
}
void clear_all_enemy(enemy* p)
{
	static enemy* T;
	if (p)
	{
		T = head_enemy;
		head_enemy = head_enemy->Pt;
		free(T);
		clear_all_enemy(head_enemy);
	}
}