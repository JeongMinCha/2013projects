#include "DisjointSet.h"

int main(void)
{
	int a=1, b=2, c=3, d=4;

	DisjointSet * set1 = MakeSet(&a);
	DisjointSet * set2 = MakeSet(&b);
	DisjointSet * set3 = MakeSet(&c);
	DisjointSet * set4 = MakeSet(&d);

	printf("set1==set2: %d \n",
		FindSet(set1)==FindSet(set2));

	UnionSet(set1, set3);
	printf("set1==set3: %d \n",
		FindSet(set1)==FindSet(set3));

	UnionSet(set3, set4);
	printf("set3==set4: %d \n",
		FindSet(set4)==FindSet(set4));

	return 0;
}