#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _edge
{
	int v1;		// start
	int v2;		// arrive
	int weight;
} Edge;

typedef struct _heapStruct
{
	int Capacity;
	int Size;
	Edge * head;
} HeapStruct;

typedef struct _disjointset
{
	struct _disjointset * parent;
} DisjointSet;

/* Heap function */
void HeapInit(HeapStruct * heap);
void insert_array(HeapStruct * heap, Edge edge);
int HIsEmpty(HeapStruct * heap);
void buildHeap(HeapStruct * heap);
Edge deleteMin(HeapStruct * heap);
void print(HeapStruct * heap);

/* DisjointSet fuction */
void DisjInit(DisjointSet * set);

void HeapInit(HeapStruct * heap)
{
	int i=0;
	heap->Capacity = 1000;
	heap->Size = 0;
	heap->head = (Edge*)malloc(sizeof(Edge)*(heap->Capacity+1));
}

void insert_array(HeapStruct * heap, Edge edge)
{
	Edge * newEdge = (Edge*)malloc(sizeof(Edge));
	newEdge->v1 = edge.v1;
	newEdge->v2 = edge.v2;
	newEdge->weight = edge.weight;

	heap->head[++heap->Size] = *newEdge;
}

int HIsEmpty(HeapStruct * heap)
{
	if(heap->Size == 0)
		return 1;
	else
		return 0;
}

void buildHeap(HeapStruct * heap)
{
	unsigned int n=heap->Size, i=n/2;
	unsigned int parent, child;
	Edge tmpEdge;

	for(;;)
	{
		if(i>0){
			i--;
			tmpEdge = heap->head[i];
		}
		else{
			n--;
			if(n==0)
				return;
			tmpEdge = heap->head[n];
			heap->head[n] = heap->head[0];
		}

		parent = i;
		child= i*2+1;

		while(child<n)
		{
			// Choose the largest child.
			if(child+1<n && heap->head[child+1].weight>heap->head[child].weight)
				child++;

			// if any child is bigger than the parent
			if(heap->head[child].weight > tmpEdge.weight)
			{
				heap->head[parent] = heap->head[child];
				parent = child;
				child = parent*2 + 1;
			}
			else
				break;
		}

		heap->head[parent] = tmpEdge;
	}
}

Edge deleteEdge(HeapStruct * heap, Edge edge)
{
	int idx, i;
	Edge dEdge;
	Edge tmpEdge = heap->head[1];

	for(idx=1; idx<=heap->Size; idx++){
		if(heap->head[idx].v1 == edge.v1 &&
			heap->head[idx].v2 == edge.v2 &&
			heap->head[idx].weight == edge.weight)
			break;
	}
	dEdge = heap->head[idx];
	/* After this loop, 'idx' means an element to delete */

	heap->Size --;
	for(i=idx; i<=heap->Size; i++){
		heap->head[i] = heap->head[i+1];
	}

	return dEdge;
}

Edge deleteMin(HeapStruct * heap)
{
	int i, child;
	Edge MinElem,LastElem;

	if(HIsEmpty(heap))
		exit(-1);

	MinElem = heap->head[1];
	LastElem = heap->head[heap->Size--];

	for(i=1; i*2<=heap->Size; i=child)
	{
		child = i*2;
		if(child != heap->Size &&
			heap->head[child+1].weight < heap->head[child].weight)
			child++;

		if(LastElem.weight > heap->head[child].weight)
			heap->head[i] = heap->head[child];

		else
			break;
	}

	heap->head[i] = LastElem;

	return MinElem;
}

void RevertHeap(HeapStruct * From, HeapStruct * To)
{
	int i=1;
	Edge tmpEdge;
	
	while(!HIsEmpty(From)){
		tmpEdge = deleteMin(From);
		To->head[From->Size-i+1] = tmpEdge;
		i++;
	}
}

void print(HeapStruct * heap)
{
	int i=0;
	Edge tmpEdge;

	while(!HIsEmpty(heap)){
		tmpEdge = deleteMin(heap);
		printf("(%d,%d,%d)\n",
			tmpEdge.v1, tmpEdge.v2, tmpEdge.weight);
	}
}

DisjointSet * find(DisjointSet * set)
{
	while (set->parent != NULL)
	{
		set = set->parent;
	}

	return set;
}

void Union(DisjointSet * set1, DisjointSet * set2)
{
	set2 = find(set2);
	set2->parent = set1;
}

int CheckMST(DisjointSet * set)
{
	int check=0, i;
	int len = sizeof(set)/sizeof(DisjointSet)-1;

	DisjointSet * tmp = find(&set[1]);
	for(i=1; i<=len; i++){
		// 각 정점들 중에 다른 대표값을 가지는 정점이 있다면 MST가 깨진 것.
		if(find(&set[i]) != tmp)
			check = 1;
	}

	if(check==0)
		return 1;
	else
		return 0;
}

void Kruskal(DisjointSet * set, HeapStruct * newheap)
{
	/* 이 알고리즘에 들어가기 앞서, 디스조인트셋에는 정점의 정보가
	힙스트럭트에는 간선의 정보가 들어가 있고, 힙스트럭트는 이미 내림차순으로
	정렬된 상태이다. */
	int idx=1;
	int setlen = sizeof(set)/sizeof(DisjointSet)-1;

	while(1)
	{
		// MST가 아닌 상태면
		if(CheckMST(set) == 0){
			// 다음으로 가중치 큰 간선을 제거
			idx++;
			continue;

			// 간선의 수가 정점의 수보다 하나 적을 때 알고리즘 종료
			if(newheap->Size == setlen-1)
				break;
		}

		// 가중치 가장 큰 간선 제거
		deleteEdge(newheap, newheap->head[idx++]);
	}
}

int main(void)
{
	int i,j,k, idx=0;

	int nv;		// the number of vertices. from 1
	int ne;		// the number of edges.

	Edge * edge;
	Edge tmp;

	HeapStruct heap;
	HeapStruct newheap;
	DisjointSet * set;
	int * parent_arr;
	
	HeapInit(&heap);
	HeapInit(&newheap);

	/* input the number of vertices and edges */
	scanf("%d", &nv);
	scanf("%d", &ne);
	edge = (Edge*)malloc(sizeof(Edge)*ne);
	set=(DisjointSet*)malloc(sizeof(DisjointSet)*(nv+1));
	parent_arr=(int*)malloc(sizeof(int)*(nv+1));

	for(i=1; i<=nv; i++)
		set[i].parent = NULL;

	/* input the information of edges */
	for(i=0; i<ne; i++){
		scanf("%d,%d,%d",
			&tmp.v1, &tmp.v2, &tmp.weight);
		edge[idx++] = tmp;
		insert_array(&heap, tmp);
		Union(&set[tmp.v1], &set[tmp.v2]);
	}

	buildHeap(&heap);
	RevertHeap(&heap, &newheap);
	Kruskal(set, &newheap);
	//print(&heap);
	
	return 0;
}