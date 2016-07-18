#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define inf 99999

typedef struct _city
{
	char name[20];
	double x;		// longitude
	double y;		// latitude
} City;

double distance(City * cities, int i, int j);
void printPath(City * cities, int ** pred, int start, int arrive);
void findShortestPathsFW(int line, City * cities, char * start, char * arrive, int radius, double ** dist, int ** pred);

int main(void)
{
	int line = 0, i;
	City *cities;
	char str[100], *ptr;
	FILE * fp = fopen("cities.txt", "r");
	char input[100];
	int radius;
	char start[50], arrive[50];
	double ** dist;
	int ** pred;
	
	// Set-up "line" as the line number of file "cities.txt";
	fgets(str, sizeof(str), fp);		// for ignoring the first meaningless line(#name...)
	while(fgets(str, sizeof(str), fp) != NULL)
		line ++;
	
	/* Dynamic Allocation */
	cities = (City*)malloc(sizeof(City)*line);
	dist = (double**)malloc(sizeof(double*)*line);
	for(i=0; i<line+1; i++)
		dist[i] = (double*)malloc(sizeof(double)*line);
	pred = (int**)malloc(sizeof(int*)*line);
	for(i=0; i<line+1; i++)
		pred[i] = (int*)malloc(sizeof(int)*line);

	/* Take the information from the given file */
	fseek(fp, 0, 0);
	for(i=0; i<=line; i++)
	{
		fgets(str, sizeof(str), fp);
		ptr = strtok(str, "\t");
		strcpy(cities[i].name, ptr);
		ptr = strtok(NULL, "\t");
		cities[i].x = atof(ptr);
		ptr = strtok(NULL, "\t");
		cities[i].y = atof(ptr);
	}

	printf("Radius\n");
	scanf("%s", input);	
	getchar();
	radius = atoi(input);

	while(1)
	{
		printf("Start\n");
		gets(start);
			if(!strcmp(start, "Quit")) break;

		printf("Destination\n");
		gets(arrive);
			if(!strcmp(arrive, "Quit")) break;

		findShortestPathsFW(line, cities, start, arrive, radius, dist, pred);
	}

	fclose(fp);
	return 0;
}

double distance(City * cities, int i, int j)
{
	double dist = sqrt((cities[i].x-cities[j].x)*(cities[i].x-cities[j].x) +
		(cities[i].y-cities[j].y)*(cities[i].y-cities[j].y));
	return dist;
}

void printPath(City * cities, int ** pred, int start, int arrive)
{
	int i,j;
	i = pred[start][arrive];

	if(pred[i][arrive] != -1)
		printPath(cities, pred, i, arrive);

	printf("<- %s ", cities[i].name);

	if(pred[start][i] != -1)
		printPath(cities, pred, start, i);
}

void findShortestPathsFW(int line, City * cities, char * start, char * arrive, int radius, double ** dist, int ** pred)
{
	int i,j,k;
	int src, dst;	// src = start, dst = destination

	// Find the start point. src means "source"; "start"
	for(i=1; i<line+1; i++){
		if(!strcmp(start, cities[i].name)){
			src = i;
			break;
		}
	}

	// Find the end point. dst means "destination"; "arrive"
	for(i=1; i<line+1; i++){
		if(!strcmp(arrive, cities[i].name)){
			dst = i;
			break;
		}
	}

	/* Floyd-Warshall Algorithm */
	// First step; set-up distances.
	for(i=1; i<line+1; i++)
	{
		for(j=1; j<line+1; j++)
		{
			if(cities[i].name == NULL)
				break;

			dist[i][j] = sqrt((cities[i].x-cities[j].x)*(cities[i].x-cities[j].x) +
		(cities[i].y-cities[j].y)*(cities[i].y-cities[j].y));
			//dist[i][j] = distance(cities, i-1, j-1);
			if(dist[i][j] > radius)
				dist[i][j] = inf;
			pred[i][j] = -1;
		}
	}
	// Second step; find the shortest distance.
	for(k=1; k<line+1; k++)
	{
		for(i=1; i<line+1; i++)
		{
			for(j=1; j<line+1; j++)
			{
				if(dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					pred[i][j] = k;
				}
			}
		}
	}

	// Print
	printf("%s ", cities[dst].name);
	printPath(cities, pred, src, dst);
	printf("<- %s \n", cities[src].name);
	printf("Path Length : %f \n", dist[src][dst]);
}
