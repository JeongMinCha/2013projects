#include <stdio.h>
#include <stdlib.h>

struct _HeapStruct
{
	int Capacity;
	int Size;
	int * head;
};
typedef struct _HeapStruct * HeapStruct;

/* The Functions */
void HeapInit(HeapStruct heap);
void insert_array(HeapStruct heap);
void buildHeap(HeapStruct heap);
int HIsEmpty(HeapStruct heap);
int deleteMin(HeapStruct heap);
void print(HeapStruct heap);

// Initializes the heap
void HeapInit(HeapStruct heap)
{
	heap->Capacity = 1000;
	heap->Size = 0;
	heap->head = (int*)malloc(sizeof(int)*(heap->Capacity+1));
}

// Just push inputs into the array
void insert_array(HeapStruct heap, int value)
{
	heap->head[++heap->Size]=value;
}

// returns whether the heap is empty.
int HIsEmpty(HeapStruct heap)
{
	if(heap->Size==0)
		return 1;
	else
		return 0;
}

// Builds the heap
void buildHeap(HeapStruct heap)
{
	unsigned int n=heap->Size, i=n/2;
	unsigned int parent, child;
	int tmp;

	for(;;)
	{
		if(i>0)
		{
			i--;
			tmp=heap->head[i];
		} else
		{
			n--;
			if(n==0)					// When the heap is empty
				return;					// Done!
			tmp=heap->head[n];			
			heap->head[n] = heap->head[0];
		}

		parent = i;
		child = i*2 + 1;

		while(child<n)
		{
			// Choose the largest child
			if(child+1<n && heap->head[child+1]>heap->head[child])
				child ++;

			// if any child is bigger than the parent
			if(heap->head[child] > tmp)
			{
				heap->head[parent] = heap->head[child];
				parent = child;
				child = parent*2+1;
			}
			else
				break;			// break when T's place is found.
		}

		heap->head[parent] = tmp;
	}
}

// deletes the minimum value of the heap.
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
			heap->head[i] =heap->head[Child];
		else
			break;
	}

	heap->head[i] = LastElement;
	return MinElement;
}

// prints the heap.
void print(HeapStruct heap)
{
	while(!HIsEmpty(heap))
		printf("%d ", deleteMin(heap));
	printf("\n");
}

// The main function.
int main(void)
{
	int i=0, idx=0, tmp;
	int num[100];		/* The numbers to input */

	/* Creating a heap, and initializing it */
	struct _HeapStruct heap;
	HeapInit(&heap);

	while(1)
	{
		scanf("%d", &tmp);
		if(tmp == -1)
			break;
		num[idx++] = tmp;
		insert_array(&heap, tmp);
	}

	buildHeap(&heap);
	print(&heap);

	return 0;
}
