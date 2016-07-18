#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
} Node;

int main(void)
{
	Node * p;
	int * parent;
	int num, i;

	scanf("%d", &num);
	p = (Node*)malloc(sizeof(Node*)*num);

	for(i=0; i<num; i++)
		p[i].value = i;
	for(i=0; i<num; i++)
		printf("%d ", p[i]);
	return 0;
}