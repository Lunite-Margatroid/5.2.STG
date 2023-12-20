#pragma once
#include "DynamicMemory.h"
#define PI 3.14159
#define left_edge 100
#define top_edge 30
#define right_edge 800
#define bottom_edge 930
#define High_ 960
#define Width_ 1280
typedef struct abcde
{
	double x;
	double y;
	int t;//t为存在时间
	int T;//T为出现时刻
	int healthpoint;//生命值
	int r;//半径
	bool existing;//是否存在
	int moving;//运动类型
	int shot;//子弹类型
	int type_enemy;//敌机类型
	struct abcde* Pt;
}enemy;
typedef struct abc
{
	double x;
	double y;
	bool z;
	struct abc* Pt;
}Bullet;//自机子弹
typedef struct abcdef
{
	double x;
	double y;
	double direction;
	int t;
	bool z;
	struct abcdef* Pt;
}Bullet_;//辅机子弹
typedef struct abcd
{
	double x;
	double y;
	bool z;
	bool g;//擦弹
	double vx;
	double vy;
	int r;//判定半径
	int t;//存在时间
	int shape;//外形1蓝2红3绿4半径-白
	struct abcd* Pt;
}bullet_enemy;
typedef struct xy
{
	double x;
	double y;
}XY;
typedef struct sc
{
	double x;
	double y;
	double tangle;
	bool z;
	int r;
	int t;
	struct sc* Pt;
}spellcard;
typedef struct annn
{
	double x;
	double y;
	int type_anime;//1自机子弹2子机子弹3符卡4自机5敌机6擦弹7符卡召唤8激光
	int t;
	struct annn* Pt;
	double tangle;
}anime;
typedef struct bbq
{
	double x;
	double y;
	bool z;
	double v;
	double tangle;
	int type_item;//1点2p
	struct bbq* Pt;
}Item;