#include <stdio.h>
#include <stdlib.h>

typedef struct _vertex
{
	int value;
	int indegree;
} Vertex;

typedef struct _edge
{
	int start;
	int finish;
} Edge;

typedef struct _node
{
	Vertex data;
	struct _node * next;
} Node;

typedef struct _queue
{
	Node * rear;
	Node * front;
} queue;
typedef queue * Queue;

typedef struct _amgraph
{
	int numV;
	int numE;
	int ** adjMat;
} AMGraph;

typedef AMGraph Graph;

/* Creating and Initializing graph, edge, vertex */
Graph * CreateGraph(int nv, int ne);
Edge * CreateEdge(int ne);
Vertex * CreateVertex(int nv);

/* Topological sort */
void MakeAdjacencyMatrix(Vertex * vertex, Edge * edge, Graph * graph);
void InitIndegree(Graph * graph, Vertex * vertex);

/* Queue ADT */
Queue CreateQueue(void);
int IsEmpty(Queue Q);
void Enqueue(Vertex * V, Queue * q);
Vertex Dequeue(Queue q);
void DisposeQueue(Queue Q);

/* Deletion of Vertex, edge */
Vertex * DeleteVertex(Graph * graph, Vertex * vertex, int index);
Edge * DeleteEdge(Graph * graph, Edge * edge, int index);

/* ETC */
void BubbleSort(Vertex ary[], int len);

Graph * CreateGraph(int nv, int ne)
{
	int i,j;
	Graph * graph = (Graph*)malloc(sizeof(Graph));

	graph->adjMat = (int**)malloc(sizeof(int*)*nv);
	for(i=0; i<nv; i++)
		graph->adjMat[i] = (int*)malloc(sizeof(int)*nv);
	graph->numV = nv;
	graph->numE = ne;

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
	for(i=0; i<ne; i++)
    {
        edge[i].finish = 0;
		edge[i].start = 0;
	}

	return edge;
}

Vertex * CreateVertex(int nv){
	int i;
	Vertex * vertex = (Vertex *)malloc(sizeof(Vertex)*nv);
	for(i=0; i<nv; i++){
		vertex[i].indegree = 0;
		vertex[i].value = 0;
	}

	return vertex;
}

void MakeAdjacencyMatrix(Vertex * vertex, Edge * edge, Graph * graph)
{
	int i,j,k;
	for(k=0; k<graph->numE; k++){
		for(i=0; i<graph->numV; i++){
			for(j=0; j<graph->numV; j++){
				if(edge[k].start == vertex[i].value)
					if(edge[k].finish == vertex[j].value)
						graph->adjMat[i][j] = 1;
			}
		}
	}
}

void InitIndegree(Graph * graph, Vertex * vertex)
{
	int i=0, j=0;

	for(i=0; i<graph->numV; i++){
		for(j=0; j<graph->numV; j++){
			vertex[j].indegree = 0;
		}
	}

	for(i=0; i<graph->numV; i++)
	{
		for(j=0; j<graph->numV; j++)
		{
			if(graph->adjMat[i][j] == 1)
				vertex[j].indegree ++;
		}
	}
}


Queue CreateQueue(void)
{
	Queue newQ;

	newQ = (Queue)malloc(sizeof(queue));
	if(newQ){
		newQ->front = 0;
		newQ->rear  = 0;
	}

	return newQ;
}

int IsEmpty(Queue Q)
{
	if(Q->front == NULL)
		return 1;
	else
		return 0;
}

void Enqueue(Vertex * V, Queue q)
{
	Node * newNode= (Node*)malloc(sizeof(Node));
	newNode->data = *V;
	newNode->next = NULL;

	if(q->front == NULL)
	{
		q->front = newNode;
		q->rear = newNode;
	}
	else
	{
		q->rear->next = newNode;
		q->rear = newNode;
	}
}

Vertex Dequeue(Queue q)
{
	Node * delNode;
	Vertex retVertex;

	if(IsEmpty(q))
	{
		printf("Queue Memory Eror!");
		exit(-1);
	}

	delNode = q->front;
	retVertex = delNode->data;
	q->front = q->front->next;

	free(delNode);
	return retVertex;
}

void DisposeQueue(Queue Q)
{
	free(Q);
}

Vertex * DeleteVertex(Graph * graph, Vertex * vertex, int index){
	int i=0;
	Vertex * delV = (Vertex*)malloc(sizeof(Vertex));
	delV->indegree = 0;
	delV->value = vertex[index].value;
	
	for(i=index; i<graph->numV-1; i++){
		vertex[i] = vertex[i+1];
	}
	return delV;
}

Edge * DeleteEdge(Graph * graph, Edge * edge, int index){
	int i=0;
	Edge * delE = (Edge*)malloc(sizeof(Edge));
	delE->start = edge[index].start;
	delE->finish = edge[index].finish;

	for(i=index; i<graph->numE-1; i++){
		edge[i] = edge[i+1];
	}

	return delE;
}

void BubbleSort(Vertex ary[], int len)
{
	int i, j;
	int tmp;

	for(i=0; i<len-1; i++){
		for(j=0; j<(len-1)-i; j++){
			if(ary[j].value>ary[j+1].value){
				tmp = ary[j].value;
				ary[j].value = ary[j+1].value;
				ary[j+1].value = tmp;
			}
		}
	}
}

int main(void)
{
	/* �ֿ� ������ */
	Graph * graph = (Graph*)malloc(sizeof(Graph));	// ��������� ���� �׷���
	Vertex * v_set;									// ������ ����
	Edge * e_set;									// ������ ����
	Queue que;										// ������ ������ ���� ť

	Vertex * delVertex;								// ť�� ������ ������ �ӽð���
	int i,j, k;
	int v_num;										// ������ ��
	int e_num;										// ������ ��

	/* ���� ������ ����鼭 ť�� ������ �� ����� ������ */
	int count = 0;									// ������ �� ��(indegre�� 0�� ��)���� ��
	int delCount=0;									// ������ �� ������ ��

	// The first line of the input. <Vertices>
	scanf("%d", &v_num);
	v_set = CreateVertex(v_num);
	for(i=0; i<v_num; i++)
		scanf("%d", &v_set[i].value);

	// The second line of the input. <Edges>
	scanf("%d", &e_num);
	e_set = CreateEdge(e_num);
	for(i=0; i<e_num; i++)
		scanf("%d,%d", &e_set[i].start, &e_set[i].finish);

	graph->numV = v_num;
	graph->numE = e_num;

	que = CreateQueue();
	/* ������ ��� ���� ������ �ݺ��Ѵ�. */
	while(graph->numV != 0){
		v_num = graph->numV;
		e_num = graph->numE;
		graph = CreateGraph(v_num, e_num);
		MakeAdjacencyMatrix(v_set,e_set,graph);
		InitIndegree(graph,v_set);

		count = 0;
		for(i=0; i<graph->numV; i++)
			if(v_set[i].indegree == 0)
				count ++;

		// �������� ��(indegree�� 0)�� ���� 1���� ��
		if(count == 1){
			delVertex = (Vertex*)malloc(sizeof(Vertex));

			// �� ����� & ť�� ����
			for(i=0; i<graph->numV; i++){
				if(v_set[i].indegree == 0)
				{
					delVertex = DeleteVertex(graph, v_set, i);
					graph->numV--;
					Enqueue(delVertex, que);
				}
			}

			// �� �����
			delCount = 0;
			for(i=0; i<graph->numE; i++){
				if(e_set[i].start==delVertex->value || e_set[i].finish==delVertex->value)
					delCount ++;
			}
			for(i=0; i<delCount; i++){
				for(j=0; j<graph->numE; j++){
					if(e_set[j].start==delVertex->value || e_set[j].finish==delVertex->value)
					{
						DeleteEdge(graph, e_set, j);
						graph->numE--;
					}
				}
			}
		}
		// �������� ��(indegree�� 0)�� ���� 2�� �̻��� ��
		else if(count>1){
			delVertex = (Vertex*)malloc(sizeof(Vertex)*count);

			// �� �����
			for(i=0; i<count; i++){
				for(j=0; j<graph->numV; j++){
					if(v_set[j].indegree == 0){
						delVertex[i] = *DeleteVertex(graph, v_set, j);
						graph->numV--;
						break;
					}
				}
			}

			// ���� ���� ���ÿ� ���� �� ũ�Ⱑ ���� �� ���� ���� ����� ���� �������� ����
			BubbleSort(delVertex, count);

			// ť�� ����
			for(i=0; i<count; i++){
				Enqueue(&delVertex[i], que);
			}

			// �� �����.
			for(i=0; i<count; i++){
				delCount = 0;
				for(j=0; j<graph->numE; j++){
					if(e_set[j].start==delVertex[delCount].value ||
						e_set[j].finish==delVertex[delCount].value)
						delCount ++;
				}
				for(j=0; j<delCount; j++){
					for(k=0; k<graph->numE; k++){
						if(e_set[k].start==delVertex[delCount].value||
							e_set[k].finish==delVertex[delCount].value)
						{
							DeleteEdge(graph, e_set, k);
							graph->numE--;
						}
					}
				}
			}
		}
	}

	// ť�� �ִ� �����͵� ��� ����ϱ�.
	while(!IsEmpty(que))
		printf("%d ", Dequeue(que));

	// ť �޸� ����
	DisposeQueue(que);
	return 0;
}