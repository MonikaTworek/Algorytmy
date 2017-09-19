#include <stdio.h>
#include <stdlib.h>


typedef struct NODE
{
	int number;
	struct NODE* child;
	struct NODE* parent;
}NODE;

typedef struct FIFO
{
	struct NODE* first;
	struct NODE* last;
} FIFO;

void push(FIFO* fifo, int what)
{
	struct NODE* help = (struct NODE*)malloc(sizeof(struct NODE));
	help->number = what; 
	help->child	= NULL;
	if(fifo->first == NULL && fifo->last == NULL){
		fifo->first = fifo->last = help;
		return;
	}
	fifo->last->child = help;
	fifo->last = help;
}

int pop(FIFO* fifo)
{
	struct NODE* help = fifo->first;
	if(fifo->first == NULL) {
		printf("IoIoIoIo \n");
		return -1;
	}
	int lol = help->number;
	if(fifo->first == fifo->last) {
		fifo->first = fifo->last = NULL;
	}
	else {
		fifo->first = fifo->first->child;
	}
	free(help);
	return lol;
}

int main(){
	FIFO fifo;
	fifo.first=NULL;
	fifo.last=NULL;
	push(&fifo, 4);
	push(&fifo, 3);
	push(&fifo, 2);

	int t = pop(&fifo);
	while (t != -1)
	{
		printf("%d\n", t);
		t = pop(&fifo);
	}
	system("PAUSE");
	//http://www.deon.pl/religia/rekolekcje-wielkopostne/wielki-post-2017/odnalezc-milosc-w-40-dni/art,2,wlasnie-dlatego-w-milosci-nie-oczekuj-wzajemnosci333.html
}