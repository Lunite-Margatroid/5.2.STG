#include "DynamicMemory.h"

DynamicMemory::DynamicMemory(int sizeOfObj)
{
	size = sizeOfObj;
	num = nUnit = 0;
	pointer = NULL;
	rear = front = NULL;
}

DynamicMemory::~DynamicMemory()
{
	int i;
	for(i=0;i<num;i++)
		delete(pointer[i]);
	delete(pointer);
}

char* DynamicMemory::MyMalloc()
{
	if (pointer == NULL)
	{
		pointer = new char*;
		num++;
		pointer[0] = new char[NUM_OF_UNIT*size];
		front = rear = (char*)pointer[0];
		return rear;
	}

	if (rear == (pointer[num - 1]+(NUM_OF_UNIT-1)*size))
	{
		int i = 0;
		char** temp = pointer;
		pointer = new char*[num+1];
		for (; i < num; i++)
			pointer[i] = temp[i];
		delete(temp);
		rear=pointer[num] = new char[NUM_OF_UNIT * size];
		num++;
		return rear;
	}
	rear += size;
	return rear;
}

char* DynamicMemory::MyFree()
{
	if (front == rear)//只剩下一个单元
		return front;

	if (front == (pointer[0] + (NUM_OF_UNIT - 1) * size))//到达末尾 而且不等于rear
	{
		char** temp = pointer;
		pointer = new char* [num - 1];
		int i = 0;
		for (; i < num - 1; i++)
		{
			pointer[i] = temp[i + 1];
		}
		num--;

		delete(temp[0]);
		delete(temp);
		return front = pointer[0];
	}

	front += size;
	return front;
}