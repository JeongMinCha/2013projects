#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
	int data;
	struct _node * next;
} Node;

typedef struct _queue
{
	int front;
	int rear;
	int * queArr;
} Queue;

Queue * CreateQueue(int num)
{
	Queue * newQ = (Queue*)malloc(sizeof(Queue));
	newQ->front = 0;
	newQ->rear = 0;
	newQ->queArr = (int*)malloc(sizeof(int)*num);

	return newQ;
}

int IsEmpty(Queue * q)
{
	if(q->front == q->rear)
		return 1;
	else
		return 0;
}

void Enqueue(Queue * q, int data)
{
	if((q->rear+1) == q->front)
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	q->queArr[q->rear] = data;
	q->rear++;
}

int Dequeue(Queue * q)
{
	if(IsEmpty(q))
	{
		printf("Queue is Empty!");
		exit(-1);
	}

	return q->queArr[q->front++];
}

void printQueue(Queue * q, FILE * ofp)
{
	int tmp = q->front;
	fprintf(ofp, "queue: ");
	if(IsEmpty(q))
	{
		fprintf(ofp, "empty queue!\n");
		return;
	}
	while(tmp != q->rear)
	{
		fprintf(ofp, "%d", q->queArr[tmp]);
		tmp ++;
	}
	fprintf(ofp, "\n\n");
}

int main(void)
{
	Queue * que;
	int num=0, i=0, tmp=0;
	FILE * ifp = fopen("input.txt", "rt");
	FILE * ofp = fopen("output.txt", "wt");

	if(ifp==NULL||ofp==NULL){
		printf("FILE OPEN FAILURE!\n");
		return -1;
	}

	fscanf(ifp, "%d", &num);
	que = CreateQueue(num);

	fprintf(ofp, "queue: ");
	for(i=0; i<num; i++){
		fscanf(ifp, "%d", &tmp);
		Enqueue(que, tmp);
		fprintf(ofp, "%d", que->queArr[i]);
	}
	fprintf(ofp, "\n\n");

	for(i=0; i<num; i++){
		if(!IsEmpty(que)){
			fprintf(ofp, "get: %d\n", Dequeue(que));
			printQueue(que, ofp);
		}
	}

	fclose(ifp);
	fclose(ofp);

	return 0;
}