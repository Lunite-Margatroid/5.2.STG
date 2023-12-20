#pragma once
#define NUM_OF_UNIT 512
#define NULL 0
class DynamicMemory
{
private:
	int num;			//内存块的数量
	int size;			//一个单位的大小
	int nUnit;			//已占用的unit数量
	char** pointer;		//内存块的指针
	char* front, * rear;//队列的收尾

public:
	DynamicMemory(int sizeOfObj);
	~DynamicMemory();

	char* MyMalloc();
	char* MyFree();
};