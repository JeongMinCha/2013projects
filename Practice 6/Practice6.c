#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* The Structure */
struct _HeapStruct{
	int Capacity;
	int Size;
	int *head;
};
typedef struct _HeapStruct * HeapStruct;

/* ADTs */
void HeapInit(HeapStruct heap);
int HIsFull(HeapStruct heap);
int HIsEmpty(HeapStruct heap);
void insert(HeapStruct heap, int value);
int deleteMin(HeapStruct heap);
void print(HeapStruct heap);

void HeapInit(HeapStruct heap)
{
	heap->Capacity = 10000;
	heap->Size = 0;
	heap->head = (int*)malloc(sizeof(heap->Capacity+1));
}

int HIsFull(HeapStruct heap)
{
	if(heap->Size > heap->Capacity)
		return 1;
	else
		return 0;
}

int HIsEmpty(HeapStruct heap)
{
	if(heap->Size==0)
		return 1;
	else
		return 0;
}

void insert(HeapStruct heap, int value)
{
	int i;
	if(HIsFull(heap))
	{
		fprintf(stderr, "Priority queue is Full!\n");
		return;
	}

	for(i=++heap->Size; value < heap->head[i/2]; i/=2)
		heap->head[i] = heap->head[i/2];

	heap->head[i] = value;
}

int deleteMin(HeapStruct heap)
{
	int i, Child;
	int MinElement, LastElement;

	if(HIsEmpty(heap))
		return -1;

	MinElement = heap->head[1];
	LastElement = heap->head[heap->Size--];

	for(i=1; i*2<=heap->Size; i=Child)
	{
		Child = i*2;
		if(Child != heap->Size && heap->head[Child+1] < heap->head[Child])
			Child++;

		if(LastElement > heap->head[Child])
			heap->head[i] = heap->head[Child];
		else
			break;
	}

	heap->head[i] = LastElement;
	return MinElement;
}

void print(HeapStruct heap)
{
	int i;

	for(i=1; i<=heap->Size; i++)
	{
		if(i%2==0)
			printf("\n");
		printf("%d ", heap->head[i]);

	}
}

int main(void)
{
	int num=0;				/* the number to operator. */
	char op, op2[5];		/* the variable checking the operation */

	struct _HeapStruct heap;
	HeapInit(&heap);

	do{
		scanf("%c", &op);

		switch (op)
		{
		case 'i':
			scanf("%d", &num);
			insert(&heap, num);
			break;

		case 'd':
			scanf("%s", op2);
			if(!strcmp("min", op2))
				if(deleteMin(&heap)==-1)
					printf("The heap is empty.\n");
			break;

		case 'p':
			print(&heap);
			printf("\n");
			break;

		default:
			break;
		}
	}while(op!='q');


	return 0;
}
