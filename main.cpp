#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <thread>
#include "touwenjian.h"
#pragma comment(lib,"winmm.lib")
#define AccS 0.6//自然加速度
#define CD 7//自机子弹间隔
#define cd_fuji 15//辅机cd
#define cd_spellcard 650//符卡cd
#define Speed 25//自机子弹速度
#define suofang 1//缩放
#define V0 6//自机速度
IMAGE img_bk,reimu1,reimu2,bullet1,bullet2;//背景 自机遮罩 自机 子弹遮罩 子弹
IMAGE hitpoint1, hitpoint2;//判定点
IMAGE img_bj;//大背景
IMAGE ziji1,ziji_d_l,ziji_d_r,ziji2;
IMAGE heart0, heart1, heart2, star0, star1, star2;
double position_x, position_y;//自机位置
bool position_z;
double vel_x, vel_y;//自机速度
double OriganVel = V0;//初速度
int life;//残机
int sc;//spellcard
int graze ;//擦弹次数
unsigned int tick;//计时
unsigned int imhit;//无敌帧
int power_;//火力
int point_;//点数
unsigned int score_;//分数
Bullet* head=NULL,*end=NULL;

DynamicMemory dmBullet(sizeof(Bullet));//自机子弹动态内存

extern enemy* head_enemy;
extern bullet_enemy* head_be;

extern Bullet_* head_;
extern Bullet_* end_;
extern bool exist;

extern anime* head_anm, * end_anm;
extern spellcard* head_sc;

extern Item* head_i;
void EnemyMoveFunction1(enemy* p);
void LoadEnemyImage();
void Summon_Enemy(enemy* p);
void Update_Enemy(enemy* p);
void show_enemy(enemy* p);
void Summon_head();
void hit_enemy(Bullet*, enemy*);
void Free_enemy(void);

void show_be();
void Update_be(bullet_enemy* p);
void summon_be(enemy* p);
void Free_be();
void hit_ziji(bullet_enemy*);

void show_score();
void Startup_score();

void show_(Bullet_*p);
void shot_();
void Update_();

void show_ziji();

void free_anime();
void show_anime(anime*);

void summon_sc();
void Update_spellcard();
void show_sc(spellcard*);
void fun_imhit();
void startup_item();
void show_item(Item*);
void Update_item();
void show_beijing(IMAGE*p)//大背景
{
	putimage(0,0,Width_,top_edge,p,0,0);
	putimage(0, 0, left_edge, High_, p, 0, 0);
	putimage(right_edge, top_edge, Width_-right_edge, High_-top_edge, p, right_edge, top_edge);
	putimage(left_edge, bottom_edge, right_edge-left_edge, High_-bottom_edge, p, left_edge, bottom_edge);
}
void shot()
{
	if (head == NULL)
	{
		//head = (Bullet*)malloc(sizeof(Bullet));
		head = (Bullet*)dmBullet.MyMalloc();
		end = head;
		head->x = position_x-14;
		head->y = position_y - 60;
		head->z = 1;
		//end->Pt = (Bullet*)malloc(sizeof(Bullet));
		end->Pt = (Bullet*)dmBullet.MyMalloc();
		end = end->Pt;
		end->x = position_x+14;
		end->y = position_y - 60;
		end->z = 1;
		end->Pt = NULL;
	}
	else
	{
		//end->Pt = (Bullet*)malloc(sizeof(Bullet));
		end->Pt = (Bullet*)dmBullet.MyMalloc();
		end = end->Pt;
		end->x = position_x-14;
		end->y = position_y-60;
		end->z = 1;
		//end->Pt = (Bullet*)malloc(sizeof(Bullet));
		end->Pt = (Bullet*)dmBullet.MyMalloc();
		end = end->Pt;
		end->x = position_x+14;
		end->y = position_y - 60;
		end->z = 1;
		end->Pt = NULL;
	}
}
void Update_Bullet(Bullet* p)//位置更新
{
	if (p != NULL)
	{
		p->y -= Speed;
		Update_Bullet(p->Pt);
	}
}
void Clear_Bullet(Bullet* p)//清除非head的z=0
{
	if(p!=NULL)
	if (p->Pt != NULL)
	{
		Bullet* t = p->Pt->Pt;
		if (p->Pt->z == 0)
		{
			//free(p->Pt);
			dmBullet.MyFree();
			p->Pt = t;
			Clear_Bullet(p);
		}
		else
			Clear_Bullet(p->Pt);
	}
}
void Edge_Bullet()//清除超出边界及head.z=0
{
	Bullet* t_pt; 
	if (head != NULL)
		if (head->y < -40||head->z==0)
		{
			t_pt = head->Pt;
			//free(head);
			dmBullet.MyFree();
			head = t_pt;
		}
}
void startup()
{
	imhit = 0;
	position_x = 450;
	position_y = 800;
	position_z = 1;
	vel_x = 0;
	vel_y = 0;
	tick = 0;
	life = 3;
	sc = 3;
	graze = 0;
	power_ = 100;
	point_ = 0;
	Summon_head();//载入敌机
	setbkmode(TRANSPARENT);//文字等背景
	loadimage(&img_bk, _T("material\\xishouhu.bmp"));
	loadimage(&reimu1, _T("material\\reimu1_mask.bmp"));
	loadimage(&reimu2, _T("material\\reimu1.bmp"));
	loadimage(&bullet1, _T("material\\card1.png"));
	loadimage(&bullet2, _T("material\\card_red.png"));
	loadimage(&hitpoint1, _T("material\\hit1.png"));
	loadimage(&hitpoint2, _T("material\\hit2.png"));
	loadimage(&img_bj, _T("material\\beijing.png"));
	loadimage(&ziji1, _T("material\\yinyangyu1.png"));
	loadimage(&ziji2, _T("material\\yinyangyu2.png"));
	loadimage(&heart0, _T("material\\heart0.bmp"));
	loadimage(&heart1, _T("material\\heart1.bmp"));
	loadimage(&heart2, _T("material\\heart2.bmp"));
	loadimage(&star0, _T("material\\spellcard0.png"));
	loadimage(&star1, _T("material\\spellcard1.bmp"));
	loadimage(&star2, _T("material\\spellcard2.bmp"));
	LoadEnemyImage();
	startup_item();
	Startup_score();
}
void show_Bullet(Bullet* p)
{
	if (p != NULL)
	{
		if (p->z)
		{
			putimage((int)(p->x - 10 + 0.5), (int)(p->y-10 + 0.5), &bullet1, NOTSRCERASE);
			putimage((int)(p->x - 10 + 0.5), (int)(p->y-10 + 0.5), &bullet2, SRCINVERT);
		}
		show_Bullet(p->Pt);
	}
}

void show()
{


	putimage(0, 0, &img_bk);
	if (position_z)
	{
		putimage((int)(position_x - 29 + 0.5), (int)(position_y - 46 + 0.5), &reimu1, NOTSRCERASE);
		putimage((int)(position_x - 29 + 0.5), (int)(position_y - 46 + 0.5), &reimu2, SRCINVERT);//自机
		show_ziji();//子机
	}
	if (imhit)
	{
		setlinecolor(0x8888FF);
		circle(position_x, position_y, 80);
		setlinecolor(0xCCCCFF);
		arc(position_x - 80, position_y - 80, position_x + 80, position_y + 80, PI / 2, PI / 2 + PI * imhit / 400);
	}
	if (OriganVel == 0.5 * V0)
	{
		putimage((int)(position_x-7 + 0.5), (int)(position_y-7 + 0.5), &hitpoint1, NOTSRCERASE);
		putimage((int)(position_x-7 + 0.5), (int)(position_y-7 + 0.5), &hitpoint2, SRCINVERT);
	}//判定点

	show_enemy(head_enemy);//enemy.cpp
	show_Bullet(head);//自机子弹
	
	show_(head_);//辅机子弹
	show_be();//敌机子弹
	show_sc(head_sc);
	show_anime(head_anm);
	show_item(head_i);

	setlinecolor(RED);
	setlinestyle(PS_SOLID, 5);
	rectangle(left_edge, top_edge, right_edge, bottom_edge);//边框

	show_beijing(&img_bj);
	show_score();//显示数据
	FlushBatchDraw();
}
void UpdateWithInput()
{
	static int Cd ;
	static int Cd_fuji;
	static int Cd_spellcard;
	OriganVel = V0;
	if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000))
		OriganVel = 0.5*V0;
	if (Cd)
		Cd--;
	if (Cd_fuji)
		Cd_fuji--;
	if (Cd_spellcard)
		Cd_spellcard--;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
		vel_x =-OriganVel;
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
		vel_x = OriganVel;
	if ((GetAsyncKeyState(VK_UP) & 0x8000))
		vel_y =- OriganVel;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
		vel_y = OriganVel;
	if ((GetAsyncKeyState(VK_LEFT) & GetAsyncKeyState(VK_UP) & 0x8000))
	{
		vel_x = -0.8 * OriganVel;
		vel_y = -0.8 * OriganVel;
	}
	if ((GetAsyncKeyState(VK_LEFT) & GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		vel_x = -0.8 * OriganVel;
		vel_y = 0.8 * OriganVel;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & GetAsyncKeyState(VK_UP) & 0x8000))
	{
		vel_x = 0.8 * OriganVel;
		vel_y = -0.8 * OriganVel;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & GetAsyncKeyState(VK_DOWN) & 0x8000))
	{
		vel_x = 0.8 * OriganVel;
		vel_y = 0.8 * OriganVel;
	}
	if ((GetAsyncKeyState(0x5a) & 0x8000))
	{
		if (Cd == 0&&position_z)
		{
			shot();
			Cd = CD;
		}
		if (Cd_fuji == 0&&position_z)
		{
			shot_();
			Cd_fuji = cd_fuji;
		}
	}
	if ((GetAsyncKeyState(0x58) & 0x8000))
	{
		if (Cd_spellcard == 0&&position_z&&imhit==0)
		{
			summon_sc();
			Cd_spellcard = cd_spellcard;
		}
	}
}
void UpdateWithoutInput()
{
	position_x += vel_x;
	position_y += vel_y;//自机位置更新
	if (position_x <= left_edge)
		position_x = left_edge;
	if (position_x >= right_edge)
		position_x = right_edge;
	if (position_y <= top_edge)
		position_y = top_edge;
	if (position_y >= bottom_edge)
		position_y = bottom_edge;//边界
	if (vel_x >0.01)
		vel_x -= AccS;
	if (vel_x <-0.01)
		vel_x += AccS;
	if (vel_y >0.01)
		vel_y -= AccS;
	if (vel_y <-0.01)
		vel_y += AccS;//加速度
	Update_Bullet(head);//自机子弹
	hit_enemy(head, head_enemy);//自机子弹击中判定
	Update_();//辅机子弹 位置更新 击中判定 free
	Update_spellcard();
	Edge_Bullet();//自机子弹head出边界判定,z free
	Clear_Bullet(head);//清除非head的z=0
	Update_Enemy(head_enemy);//运动，0血清理，越界=0
	Free_enemy();//free敌机
	Free_be();//敌机子弹
	free_anime();
	hit_ziji(head_be);//挨打判定
	Update_be(head_be);//敌机子弹位置更新
	summon_be(head_enemy);//敌机shot
	fun_imhit();//无敌帧
	Update_item();
}
void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();
	while (GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}
void GameStart();
bool GameOver();
int main()
{
	initgraph(suofang * Width_, suofang * High_);
	setaspectratio(suofang, suofang);
	BeginBatchDraw();
	GameStart();
	Flag_Restart:
	startup();
	while (1)
	{
		show();
		UpdateWithInput();
		UpdateWithoutInput();
		tick++;
		delay(5);
		if (life == 0)
			break;
	}
	if (GameOver())
		;
	else
		goto Flag_Restart;
	EndBatchDraw();
	closegraph();
	return 0;
}