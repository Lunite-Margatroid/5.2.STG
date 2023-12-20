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
	int t;//tΪ����ʱ��
	int T;//TΪ����ʱ��
	int healthpoint;//����ֵ
	int r;//�뾶
	bool existing;//�Ƿ����
	int moving;//�˶�����
	int shot;//�ӵ�����
	int type_enemy;//�л�����
	struct abcde* Pt;
}enemy;
typedef struct abc
{
	double x;
	double y;
	bool z;
	struct abc* Pt;
}Bullet;//�Ի��ӵ�
typedef struct abcdef
{
	double x;
	double y;
	double direction;
	int t;
	bool z;
	struct abcdef* Pt;
}Bullet_;//�����ӵ�
typedef struct abcd
{
	double x;
	double y;
	bool z;
	bool g;//����
	double vx;
	double vy;
	int r;//�ж��뾶
	int t;//����ʱ��
	int shape;//����1��2��3��4�뾶-��
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
	int type_anime;//1�Ի��ӵ�2�ӻ��ӵ�3����4�Ի�5�л�6����7�����ٻ�8����
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
	int type_item;//1��2p
	struct bbq* Pt;
}Item;