#include "touwenjian.h"
#include <graphics.h>
#include <math.h>

#define time__ 100//子机子弹存在时间

Bullet_* head_ = NULL;
Bullet_* end_ = NULL;
XY x_y;

extern enemy* head_enemy;
extern int power_;
extern double position_x,position_y;
extern unsigned int score_;
bool exist = 0;//是否存在有效敌机
static double distance;

DynamicMemory dmWhiteBullet(sizeof(Bullet_));

void build_anime2(Bullet_* p);

XY seekenemy(enemy*en)//索敌
{
	static XY x_y;
	static double t;
	if (en)
	{
		if (en->existing)
		{
			exist = 1;
			t = pow(position_x - en->x, 2) + pow(position_y - en->y, 2);
			if (distance > t)
			{
				distance = t;
				x_y.x = en->x;
				x_y.y = en->y;
			}
		}
		seekenemy(en->Pt);
	}
	return x_y;
}
void guide_(Bullet_*p,XY x_y)//导向
{
	if (p)
	{
		if(p->z)
			p->direction = atan2(x_y.y - p->y, x_y.x - p->x);
		guide_(p->Pt, x_y);
	}
}
void shot_()
{
		if (head_ == NULL)
		{
			//head_ = (Bullet_*)malloc(sizeof(Bullet_));
			head_ = (Bullet_*)dmWhiteBullet.MyMalloc();
			end_ = head_;
			head_->x = position_x+50;
			head_->y = position_y;
			head_->z = 1;
			head_->direction = -PI / 3;
			head_->t = time__;
			//end_->Pt = (Bullet_*)malloc(sizeof(Bullet_));
			end_->Pt = (Bullet_*)dmWhiteBullet.MyMalloc();
			end_ = end_->Pt;
			end_->x = position_x -50;
			end_->y = position_y;
			end_->z = 1;
			end_->direction = -PI * 2 / 3;
			head_->t = time__;
			end_->Pt = NULL;
		}
		else
		{
			//end_->Pt = (Bullet_*)malloc(sizeof(Bullet_));
			end_->Pt = (Bullet_*)dmWhiteBullet.MyMalloc();
			end_ = end_->Pt;
			end_->x = position_x + 50;
			end_->y = position_y;
			end_->z = 1;
			end_->direction = -PI / 3;
			end_->t = time__;
			//end_->Pt = (Bullet_*)malloc(sizeof(Bullet_));
			end_->Pt = (Bullet_*)dmWhiteBullet.MyMalloc();
			end_ = end_->Pt;
			end_->x = position_x - 50;
			end_->y = position_y;
			end_->z = 1;
			end_->direction = -PI * 2 / 3;
			end_->t = time__;
			end_->Pt = NULL;
		}
}
void move_(Bullet_*p)//子机子弹位置更新 读秒
{
	if (p)
	{
		p->t--;
		if (p->z)
		{
			p->x += 10 * cos(p->direction);
			p->y += 10 * sin(p->direction);
		}
		move_(p->Pt);
	}
}
void free_()//释放
{
	static Bullet* T;
	if (head_)
	{
		Bullet_* T = head_;
		if (head_->t <= 0)
		{
			head_ = head_->Pt;
			//free(T);
			dmWhiteBullet.MyFree();
		}
	}
}
void free__()
{
	static Bullet* T;
	if (head_)
	{
		Bullet_* T = head_;
		head_ = head_->Pt;
		//free(T);
		dmWhiteBullet.MyFree();
	}
}
void hit_(Bullet_* b, enemy* e)
{
	static double distance2;
	if (b && e)
	{
		if (b->z && e->existing)
		{
			distance2 = pow(b->x - e->x, 2) + pow(b->y - e->y, 2);
			if ((int)(distance2) <= (e->r + 15) * (e->r + 15))
			{
				e->healthpoint -= (5+power_/20);
				score_ += 10;
				b->z = 0;
				build_anime2(b);
			}
		}
		hit_(b, e->Pt);
	}
	if (b && !e)
		hit_(b->Pt, head_enemy);
}
void show_(Bullet_*p)
{
	if (p)
	{
		if (p->z)
		{
			setlinestyle(PS_SOLID,4);
			setlinecolor(0xFFFFFF);
			circle((int)(p->x+0.5), (int)(p->y+0.5), 15);
			circle((int)(p->x + 0.5), (int)(p->y + 0.5), 10);
			circle((int)(p->x + 0.5), (int)(p->y + 0.5), 5);
		}
		show_(p->Pt);
	}
}
void guide_sc(spellcard*, XY);
void Update_()
{
	if (head_enemy)
	{
		exist = 0;//没有有效敌机
		distance = 9000000;
		x_y = seekenemy(head_enemy);//索敌，若存在有效敌机 exist=1
		if (exist)
			guide_(head_, x_y);//导向
	}
	move_(head_);//位置更新 读秒
	free_();//释放内存
	hit_(head_,head_enemy);//击中判定
}
void clear_fuji_bullet(Bullet_* p)
{
	static Bullet_* T;
	if (p)
	{
		T = head_;
		head_ = head_->Pt;
		//free(T);
		dmWhiteBullet.MyFree();
		clear_fuji_bullet(head_);
	}
}