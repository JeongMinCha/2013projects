#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// RAND(a,b) has the random value from a to b. 
#define RAND(a,b) rand()%(b-a+1)+a

typedef struct _disjointset
{
	int * maze;
	int size;
	int scale;
} DisjointSet;

void Init(DisjointSet * set);
void Union(DisjointSet * set, int i, int j);
int find(DisjointSet * set, int i);
void make_maze(DisjointSet * set);
void print_maze(DisjointSet * set);

void Init(DisjointSet * set)
{
	int i;

	set->maze = (int*)malloc(sizeof(int)*(set->scale+1));

	for(i=1; i<=set->scale; i++)
		set->maze[i] = 0;
}

void Union(DisjointSet * set, int i, int j)
{
	set->maze[i] = j;
}

int find(DisjointSet * set, int i)
{
	while(set->maze[i] != 0)
		i = set->maze[i];
	
	// After loop, i has the value of the representative of a union.
	return i;
}

void make_maze(DisjointSet * set)
{
	int x, y;

	// Until 1th elem and last elem has the same representative value.
	while(find(set, 1) != find(set, set->scale))
	{
		x = RAND(1,set->scale);
		y = RAND(0,1);		// 0: right, 1: down
		/* We don't need to check left, up */

		// right and down but I can't go outside. I will "continue";
		if(y==0){
			if((x-1)%set->size == set->size-1)
				continue;
		}
		else{
			if((x-1)/set->size == set->size-1)
				continue;
		}

		switch(y)
		{
		case 0:
			y = x+1;
			break;
		case 1:
			y = x+set->size;
			break;
		}

		if(find(set,x) != find(set, y))
			Union(set, x, y);
	}
}

void print_maze(DisjointSet * set)
{
	int i, j;
	
	for(i=0; i<set->size; i++)
		printf("天");
	printf("\n");

	for(i=0; i<set->size; i++)
	{		
		if(i == 0)
			printf("  ");
		else
			printf("太");

		for(j=1; j<set->size; j++)
		{
			// If unioned with right, print empty.
			if(set->maze[i*set->size+j] == i*set->size+j+1)
				printf("  ");
			else
				printf("太");
		}

		if(i == set->size-1)
			printf("\n ");
		else 
		{
			printf("太\n ");
			for(j=1; j<=set->size; j++)
			{
				// If unioned with down, print empty.
				if(set->maze[i*set->size + j] == (i+1)*set->size + j)
					printf("﹛");
				else
					printf("天");
			}
			printf("\n");
		}
	}

	for ( i=1; i<=set->size; i++ )
		printf("天");

	printf("\n");
}

int main(void)
{
	DisjointSet * set;
	int size;		
	int scale;		// The scale of maze

	srand((unsigned int)time(NULL));
	
	/* Initializing the DisjointSet */
	set = (DisjointSet *)malloc(sizeof(DisjointSet));
	scanf("%d", &set->size);
	set->scale = set->size*set->size;
	Init(set);

	make_maze(set);

	print_maze(set);

	return 0;
}
