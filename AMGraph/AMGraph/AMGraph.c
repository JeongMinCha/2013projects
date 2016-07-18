#include <stdio.h>
#include <stdlib.h>
#include "AMGraph.h"

void GraphInit(Graph * pg, int nv)
{
	int i,j;

	pg->adjMat = (int**)malloc(sizeof(int*)*nv);
	for(i=0; i<nv; i++)
		pg->adjMat[i] = (int*)malloc(sizeof(int)*nv);
	pg->numV = nv;
	pg->numE = 0;

	for(i=0; i<nv; i++){
		for(j=0; j<nv; j++){
			pg->adjMat[i][j] = 0;
		}
	}
}

void GraphDestroy(Graph * pg)
{
	if(pg->adjMat != NULL)
		free(pg->adjMat);
}

void AddEdge(Graph * pg, int fromV, int toV)
{
	pg->adjMat[fromV][toV] = 1;
}

void ShowGraphEdgeInfo(Graph * pg)
{
	int i;
	int vx;

	for(i=0; i<pg->numV; i++)
	{
		printf("[Point %d]\n", i+1);
	}
	printf("\n");
}

void MakeAdjacencyMatrix(Graph * pg, int nv)
{
	GraphInit(pg, nv);
}

void InitIndegree(Graph * pg, int nv)
{
	
}
