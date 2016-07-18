#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND(a,b) rand()%(b-a+1)+a;

typedef struct _DisjointSets
{
	int rank;
	int value;
	struct _DisjointSets * parent;
} DisjointSets;

typedef struct _Wall
{
	int a;
	int b;
	int value;
} Wall;

/* The functions */
void init(DisjointSets * sets);
void Union(DisjointSets * sets, int i, int j);
int find(DisjointSets * sets, int i);

void init(DisjointSets * sets)
{
	sets->parent = sets;
	sets->rank = 0;
	sets->value = 0;
}

DisjointSets* FindName(DisjointSets * sets)
{
	DisjointSets* tmpset = sets;
	while(tmpset->parent != tmpset)
		tmpset = tmpset->parent;

	return tmpset;
}

int find(DisjointSets * sets, int i)
{
	int j=0;
	DisjointSets * tmp=NULL;

	while(sets[j].value != i)
		j++;

	tmp = FindName(&sets[j]);

	return tmp->value;
}

void Union(DisjointSets * sets, int i, int j)
{	
	DisjointSets * tmp = &sets[0];
	if(sets[j].value > sets[i].value){
		tmp = FindName(&sets[i]);
		sets[j].rank = tmp->rank - 1;
		tmp->parent = &sets[j];
	}
	else{
		tmp = FindName(&sets[j]);
		sets[j].rank = tmp->rank - 1;
		tmp->parent = &sets[i];
	}
}

int main(void)
{	
	int i=0, j=0, count=0;
	int size, space, wallnum;
	int a, b, dir;
	DisjointSets * RootSet = NULL;
	Wall * Walls = NULL;
	srand((unsigned int)time(NULL));

	do {
		printf("Set the size of the maze>");
		scanf("%d", &size);
	}while(size<=0);
	space = size*size;
	wallnum = 2*size*(size-1);

	RootSet = (DisjointSets*)calloc(space, sizeof(DisjointSets));
	Walls = (Wall*)calloc(wallnum, sizeof(Wall));

	// Initializing the DisjointSets
	for(i=0; i<space; i++){
		init(&RootSet[i]);
		RootSet[i].value = i+1;
	}

	// Initializing the vertical walls
	for(i=0; i<size-1; i++){
		for(j=0; j<size; j++){
			Walls[count].a = size*i+j+1;
			Walls[count].b = size*i+j+size+1;
			Walls[count].value = 1;
			count++;
		}
	}
	// Initializing the horizontal walls
	for(i=0; i<size; i++){
		for(j=0; j<size-1; j++){
			Walls[count].a = size*i+j+1;
			Walls[count].b = size*i+j+2;
			Walls[count].value = 1;		// There's a wall.
			count++;
		}
	}

	do{
		a = RAND(1,space);
		dir = RAND(1,2);
		switch(dir)
		{
		case 1:	// South
			if((size*(size-1)+1)<=a && a<=space)
				continue;
			b = a + size;
			break;
		case 2:	// East
			if(a%size==0)
				continue;
			b = a + 1;
			break;
		}
		Union(RootSet, a-1, b-1);
		//for(i=0; i<wallnum; i++)
		//{
		//	if(Walls[i].a == a)
		//		if(Walls[i].b == b)
		//			Walls[i].value = 0;
		//}
	}while(find(RootSet,1) == find(RootSet,space));

	/* I have to just print it :( ... */

	return 0;
}