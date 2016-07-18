#ifndef __AM_GRAPH__
#define __AM_GRAPH__

typedef struct _node
{
	int value;
} Node;

typedef struct _amgraph
{
	int numV;
	int numE;
	int ** adjMat;
} AMGraph;

typedef AMGraph Graph;

void GraphInit(Graph * pg, int nv);

void GraphDestroy(Graph * pg);

//void MakeAdjacencyMatrix();
void InitIndegree();
Queue CreateQueue(void);
void Enqueue(Vertex V, Queue Q);
int IsEmpty(Queue Q);
void DisposeQueue(Queue Q);

#endif