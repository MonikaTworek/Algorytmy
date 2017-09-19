#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 1000
int count = 0;

typedef struct NODE
{
	struct NODE* child;
	struct NODE* parent;
	int number;
} NODE;

void push(NODE** list, int element)
{
	NODE* n = (NODE*)malloc(sizeof(NODE));
	n->number = element;
	count++;
	if (*list != NULL)
	{
		n->child = *list;
		n->parent = (*list)->parent;
		n->parent->child = n;
		(*list)->parent = n;
	}
	else
	{
		n->child = n;
		n->parent = n;
		*list = n;
	}
}

int get(NODE** list, int i)
{
	NODE* cursor = *list;
	if (i < count / 2)
	{
		for (int j = 0; cursor != NULL && j < i; j++)
			cursor = cursor->child;
		if (cursor != NULL) return cursor->number;
		else return -1;
	}
	else
	{
		for (int j = 0; cursor != NULL && j < count - i; j++)
			cursor = cursor->parent;
		if (cursor != NULL) return cursor->number;
		else return -1;
	}
}


void merge(NODE** listA, NODE** listB)
{
	if (*listB == NULL) return;
	if (*listA == NULL)
	{
		*listA = *listB;
	}
	else
	{
		NODE* endA = (*listA)->parent;
		(*listA)->parent = (*listB)->parent;
		endA->child = (*listB);
		NODE* endB = (*listB)->parent;
		(*listB)->parent = endA;
		endB->child = (*listA);
	}
}

void wee(){
	NODE* list = NULL;
	srand(time(NULL));
	clock_t start, stop;
	double average;
	int number;
	for (int i = 0; i < SIZE; i++)
		push(&list, rand() % SIZE);

	FILE *f;
	f = fopen("niktNieNosiNaszywek.csv", "w");
	for (int i = 0; i < SIZE; i++)
	{
		average = 0;
		for (int j = 0; j < SIZE; j++)
		{
			start = clock();
			number = get(&list, i);
			stop = clock();
			average = average + (double)(stop - start);
		}
		average = average / SIZE;
		fprintf(f, "%d,%f\n", i, average);
	}
	fclose(f);


	f = fopen("ryczyRannyRys.csv", "w");
	for (int i = 0; i < SIZE; i++)
	{
		average = 0;
		for (int j = 0; j < SIZE; j++)
		{
			start = clock();
			number = get(&list, rand() % SIZE);
			stop = clock();
			average = average + (double)(stop - start);
		}
		average = average / SIZE;
		fprintf(f, "%d,%f\n", i, average);
	}
	fclose(f);	
}


int main(int argc, char* argv[])
{
	wee();
	NODE* listA = NULL;
	push(&listA, 1);
	push(&listA, 2);
	push(&listA, 3);
	push(&listA, 4);
	NODE* listB = NULL;
	push(&listB, 5);
	push(&listB, 6);
	merge(&listA, &listB);

	for (int i = 0; i < 6; i++)
		printf("%d\n", get(&listA, i));

	system("PAUSE");

	return 0;
}