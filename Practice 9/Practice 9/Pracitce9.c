#include <stdio.h>
#include <stdlib.h>

#define inf INT_MAX

int * dist;
int * pred;

typedef struct _vertex
{

} Vertex;

typedef struct _node
{
	Vertex vertex;
	int priority;
} Node;

typedef struct _edge
{
	int start;
	int end;
	int weight;
} Edge;

typedef struct _amgraph
{
	int numV;
	int numE;
	int ** adjMat;
} Graph;

typedef struct _heapstruct
{
	int capacity;
	int size;
	Node * head;
} Heap;

/* Creating and Initializing graph, edge, vertex */
Graph * CreateGraph(int nv, int ne);
Edge * CreateEdge(int ne);
Vertex * CreateVertex(int nv);

Graph * CreateGraph(int nv, int ne)
{
	int i,j;

	Graph * graph = (Graph*)malloc(sizeof(Graph));

	graph->adjMat = (int **)malloc(sizeof(int*)*nv);
	for(i=0; i<nv; i++)
		graph->adjMat[i] = (int*)malloc(sizeof(int)*nv);
	graph->numE = ne;
	graph->numV = nv;

	for(i=0; i<nv; i++){
		for(j=0; j<nv; j++){
			graph->adjMat[i][j] = 0;
		}
	}

	return graph;
}

Edge * CreateEdge(int ne){
	int i;
	Edge * edge = (Edge*)malloc(sizeof(Edge)*ne);
	for(i=0; i<ne; i++){
        edge[i].end = 0;
		edge[i].start = 0;
		edge[i].weight = 0;
	}

	return edge;
}

Vertex * CreateVertex(int nv){
	int i;
	Vertex * vertex = (Vertex *)malloc(sizeof(Vertex)*nv);
	for(i=0; i<nv; i++)
		vertex[i] = 0;

	return vertex;
}

void Init(int *d, int *pred);
void Insert(Heap * heap, int key, int value);
void BuildHeap(Heap *heap);
Node DeleteMin(Heap *heap);
int isEmpty(Heap * heap);
void DecreasePriority(Heap * heap, int key, int value);

// Heap에 value, pr을 가지는 Node를 집어넣는다.
void Insert(Heap * heap, Vertex value, int pr)
{
	int i;
	int idx = heap->size+1;
	Node newNode = {value, pr};

	if(isFull(heap)){
		printf("Priority queue is Full!\n");
		return;
	}

	while(idx != 1)
	{
		if(pr < (heap->head[idx/2].priority)){
			heap->head[idx] = heap->head[idx/2];
			idx = idx/2;
		}
		else
			break;
	}

	heap->head[idx] = newNode;
	heap->size += 1;
}

Node deleteMin(Heap * heap)
{
	int i, child;
	Node minElem, lastElem;

	if(isEmpty(heap))
		return;

	minElem = heap->head[1];
	lastElem = heap->head[heap->size--];

	for(i=1; i*2<=heap->size; i=child)
	{
		child = i*2;
		if(child != heap->size && heap->head[child+1].priority<heap->head[child].priority)
			child++;

		if(lastElem.vertex > heap->head[child].vertex)
			heap->head[i] = heap->head[child];
		else
			break;
	}

	heap->head[i] = lastElem;
	return minElem;
}

int isFull(Heap * heap)
{
	if(heap->size > heap->capacity)
		return 1;
	else
		return 0;
}

int isEmpty(Heap * heap)
{
	if(heap->size == 0)
		return 1;
	else
		return 0;
}

int main(void)
{
	int * pred;
	int * dist;
	int * state;
	int i,j,k;
	int nv;// number of vertices
	int ne;// number of edges
	Vertex * sv;// set of vertices
	Edge * se;// set of edges
	Graph * graph;
	int start; int end; // Input

	scanf("%d", &nv);
	scanf("%d", &ne);

	graph = CreateGraph(nv, ne);
	sv = CreateVertex(nv);
	se = CreateEdge(ne);
	for(i=0; i<ne; i++){
		scanf("%d,%d,%d", 
			&se[i].start, &se[i].end, &se[i].weight);
	}

	do{
		scanf("%d %d", &start, &end);
	}while(0);

	return 0;
}

void BuildHeap(Heap * heap)
{
	heap->capacity = 10000;
	heap->size = 0;
	heap->head = (Node*)malloc(sizeof(Node)*(heap->capacity+1));
}

void MakeAdjacencyMatrix(Graph * graph, Vertex * vertex, Edge * edge)
{
	int i,j,k;
	for(k=1; k<=graph->numE; k++){
		for(i=1; i<=graph->numV; i++){
			for(j=1; j<=graph->numV; j++){

				if(i==j)
					graph->adjMat[i][j] = 0;
				if(i==edge[k].start-1){
					if(j==edge[k].end-1)
						graph->adjMat[i][j] = edge[k].weight;
				}
				else{
					graph->adjMat[i][j] = inf;
				}
			}
		}
	}
}

void Dijkstra(Graph * pg, int * d, int * pred, Heap * heap, int start, int arrive){
	int i,j,min,tmp,k;

	int i,j;
	int size = pg->numV*pg->numV;	// size of adjMatrix

	// num = num_Vertex;
	for(k=start, i=start; k<start+pg->numV; k++){
		min = inf;		// min은 다음 턴에 선택할 노드의 잠정적인 거리값 중 최소값을 저장할 변수.

		for(i=1; i<=pg->numV; i++){
			if(i != j){
				if(state[i] == 0 && pg->adjMat[i][j] < inf){
					//미방문 상태이고 i와 인접하고 있는 노드 선택
					if(dist[j] > dist[i] + pg->adjMat[i][j]){
						dist[i] = dist[i] + pg->adjMat[i][j];
						pred[j] = i;

						if(dist[j] < min){
							tmp = j; // tmp는 최소값을 가지는 노드의 번호를 임시 저장하는 변수
							min = dist[j];
						}
					}
					else{
						if(dist[j] < min){
							tmp = j;
							min = dist[j];
						}
					}
				}
			}
			// i==j 인 경우, 즉 자기 자신과의 비교는 무시한다.
			else{
				continue;	
			}
		}
		state[tmp] = 1;		// 최소값을 가지는 노드를 방문상태로 바꾼다.
		i = tmp;
	}
}
				
void Init(int *d, int *pred)
{
	int i;
	int nv = sizeof(d)/sizeof(int);

	for(i=0; i<nv; i++){
		d[i] = 0;
		pred[i] = 0;
	}
}

