#include<stdio.h>
#include"linkedlist.h"
#include"dbg.h"

int compare(void* arg1, void* arg2)
{
	int* a = (int*)arg1;
	int* b = (int*)arg2;
	if(*a < *b)
		return -1;
	else if(*a > *b)
		return 1;
	else
		return 0;
}

int main(void)
{
	LIST* list;

	list = createList(compare);

	check_mem(list)
	destroyList(list);
	return 0;
error:
	return -1;
}
