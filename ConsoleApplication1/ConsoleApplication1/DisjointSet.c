#include "DisjointSet.h"

void UnionSet(DisjointSet * set1, DisjointSet * set2)
{
	set2 = FindSet(set2);
	set2->parent = set1;
}

DisjointSet * FindSet(DisjointSet * set)
{
	while(set->parent != NULL)
		set=set->parent;
	return set;
}

DisjointSet * MakeSet(void * newData)
{
	DisjointSet * newNode = (DisjointSet*)malloc(sizeof(DisjointSet*));
	newNode->data = newNode;
	newNode->parent = NULL;

	return newNode;
}

void DestroySet(DisjointSet * set)
{
	free(set);
}