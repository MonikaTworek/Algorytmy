#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <windows.h>
#define SIZE 1000

typedef struct NODE{
	int number;
	struct NODE* next;
}NODE;

void push(NODE** node, int jol){
	NODE* yup=(NODE*)malloc(sizeof(NODE));
	yup->number=jol;
	yup->next=NULL;
	if (*node==NULL){
		*node=yup;
	}
	else{
		NODE* help=*node;
		while(help->next!=NULL){
			help=help->next;
		}
		help->next=yup;
	}
}

int get(NODE** list, int i)
{
	NODE* cursor = *list;
	for (int j = 0; cursor != NULL && j < i; j++)
		cursor = cursor->next;
	if (cursor != NULL) return cursor->number;
	else return -1;
}

void merge(NODE** listA, NODE** listB)
{
	if (*listA == NULL)
	{
		*listA = *listB;
	}
	else
	{
		NODE* cursor = *listA;
		while (cursor->next != NULL)
			cursor = cursor->next;
		cursor->next = *listB;
	}
}

void yolo(){
	NODE* list = NULL;
	srand(time(NULL));
	double average, number;
	clock_t start, stop;
	for (int i = 0; i < SIZE; i++)
		push(&list, rand() % SIZE);
	FILE *f;
	f = fopen("normalne.csv", "w");
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
	
	f = fopen("randomowe.csv", "w");
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
	yolo();
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
		printf("%d\n",get(&listA, i));
	
	system("PAUSE");

	return 0;
}
