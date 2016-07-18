#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES		100

typedef struct node * pNode;

typedef struct node {
	int vertex;
	pNode link;
};

typedef struct {
	int count;
	pNode link;
} hdnodes;

hdnodes graph[MAX_VERTICES];

void topSort(hdnodes graph[], int n)
{
	int i,j,k,top;
	pNode ptr;
	/* create a stack of vertices with no predecessors */
	top=-1;
	for(i=0; i<n; i++){
		if(!graph[i].count){
			graph[i].count = top;
			top = i;
		}
	}
	for(i=0; i<n; i++){
		if(top==-1){
			fprintf(stderr, "\nNetwork has a cycle. Sort terminated. \n");
			exit(EXIT_FAILURE);
		}
		else
		{
			j = top;		/* unsatck a vertex */
			top = graph[top].count;
			printf("v%d, ", j);
			for(ptr=graph[j].link;ptr;ptr=ptr->link){
				/* decrease the count of the successor vertices of j */
				k = ptr->vertex;
				graph[k].count--;
				if(!graph[k].count){
					/* add vertex k to the stack */
					graph[k].count = top;
					top = k;
				}
			}
		}
	}
}

int main(void)
{
	return 0;
}