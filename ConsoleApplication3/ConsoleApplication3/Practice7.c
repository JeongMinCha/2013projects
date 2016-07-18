#include <time.h>

#include <stdio.h>

#include <stdlib.h>



#define SIZE 6

#define sSIZE SIZE*SIZE



typedef struct DisjointSet {

	int size;

	int *maze;

}Dis;



void Init(Dis *sets);

void Union(Dis *sets, int i, int j);

int Find(Dis *sets, int i);

void printmaze(Dis *sets);



int main(void)

{

	int x, y;

	Dis *sets;



	srand((unsigned int)time(NULL));



	//init

	sets = (Dis*)malloc(sizeof(Dis));

	Init(sets);

	

	while ( Find(sets, 1) != Find(sets, sSIZE) )

	{

		x = (rand()%(sSIZE))+1;		// ¿ßƒ°

		y = rand()%2;				// πÊ«‚ 0 : øÏ 1 : «œ



		//ø‹∞˚¡ˆø™

		if ( (x-1)%SIZE == SIZE-1 && y == 0 ) continue;

		else if ( (x-1)/SIZE == SIZE-1 && y == 1 ) continue;

			

		//y¡¬«•º≥¡§

		switch ( y )

		{

		case 0: y = x+1;

			break;

		case 1: y = x+SIZE;

			break;

		}



		if ( Find(sets, x) != Find(sets, y) )

			Union(sets, x, y);

	}



	printmaze(sets);

	return 0;

}



void printmaze(Dis *sets)

{

	int i, j;

	printf(" ");

	for ( i=0; i<SIZE; i++ ) printf("§—");

	printf("\n");

	for ( i=0; i<SIZE; i++ )

	{

		if ( i != 0 ) printf("§”");

		else printf("  ");

		for ( j=1; j<SIZE; j++ )

		{

			if ( sets->maze[i*SIZE+j] == i*SIZE+j+1 )

				printf("  ");

			else printf("§”");

		}

		if ( i == SIZE-1 ) printf("\n ");

		else 

		{

			printf("§”\n ");

			for ( j=1; j<=SIZE; j++ )

			{

				if ( sets->maze[i*SIZE + j] == (i+1)*SIZE + j )

					printf("°°");

				else printf("§—");

			}

			printf("\n");

		}

	}

	for ( i=1; i<=SIZE; i++ )

		printf("§—");



	printf("\n");

}



void Init(Dis* sets)

{

	int i;



	sets->size = sSIZE;

	sets->maze = (int*)malloc(sizeof(int)*sets->size);



	for ( i=1; i<=sets->size; i++ )

		sets->maze[i] = 0;

}

void Union(Dis sets[], int i, int j)

{

	sets->maze[i] = j;

}



int Find(Dis *sets, int i)

{

	while ( sets->maze[i] != 0 )

		i = sets->maze[i];



	return i;

}