#pragma once
#define NUM_OF_UNIT 512
#define NULL 0
class DynamicMemory
{
private:
	int num;			//�ڴ�������
	int size;			//һ����λ�Ĵ�С
	int nUnit;			//��ռ�õ�unit����
	char** pointer;		//�ڴ���ָ��
	char* front, * rear;//���е���β

public:
	DynamicMemory(int sizeOfObj);
	~DynamicMemory();

	char* MyMalloc();
	char* MyFree();
};