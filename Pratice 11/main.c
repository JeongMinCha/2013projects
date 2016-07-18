#include <stdio.h>
#include <stdlib.h>

typedef struct _hashtable
{
	int index;
	int table;
} HashTable;

int HashFull(HashTable *node, int tablesize);
void HashInit(HashTable *node, int tablesize);
void Insert(HashTable *node, int value, int tablesize);
void Delete(HashTable *node, int value, int tablesize);
int Find(HashTable *node, int value, int tablesize);

int HashFull(HashTable * node, int tablesize)
{
	int i=0;
	int check=1;
	for(i=0; i<tablesize; i++){
		// 지워지거나 빈 곳이 있으면 check 는 0이 됩니다.
		if(node[i].table == -100 || node[i].table == -1)
			check = 0;
	}

	return check;
}

void HashInit(HashTable * node, int tablesize)
{
	int i=0;

	for(i=0; i<tablesize; i++){
		node[i].index = i;
		node[i].table = -100;
	}
}

void Insert(HashTable *node, int value, int tablesize)
{
	int i=1;
	int hk = value%tablesize;		// Hash(k);
	int lhk;						// Local Hash(k) in while(1);

	if(HashFull(node, tablesize))
	{
		printf("This HashTable is Full!\n");
		return;
	}

	if(node[hk].table == -100 || node[hk].table == -1)
	{
		node[hk].table = value;
		return;
	}
	else
	{
		// Qudratic Probing
		while(1)
		{
			lhk = hk + i*i;
			if(node[lhk].table == -100 || node[lhk].table == -1)
			{
				node[lhk].table = value;
				return;
			}
			i++;
		}
	}
}

void Delete(HashTable *node, int value, int tablesize)
{
	int hk = value%tablesize;

	node[hk].table = -1;
}

int Find(HashTable *node, int value, int tablesize)
{
	int i=0;
	int index = -1;		// If not exist, return -1;

	for(i=0; i<tablesize; i++){
		if(node[i].table == value)
			index = i;
	}
	
	return index;
}

int main(void)
{
	int i=0;
	int tablesize;
	char op; int num;

	HashTable * hashtable;

	printf("Hash table size(m): ");
	scanf("%d", &tablesize);
	hashtable = (HashTable*)malloc(sizeof(HashTable)*tablesize);
	HashInit(hashtable, tablesize);

	while(1)
	{
		scanf("%c", &op);
		switch(op)
		{
		/* insert */
		case 'i':
			scanf("%d", &num);
			for(i=0; i<tablesize; i++)
			{
				if(hashtable[i].table == num)
					break;
			}
			Insert(hashtable, num, tablesize);
			break;
		
		/* delete */
		case 'd':
			scanf("%d", &num);
			if(Find(hashtable,num,tablesize)==-1)
				break;
			Delete(hashtable, num, tablesize);
			break;

		/* find */
		case 'f':
			scanf("%d", &num);
			if(Find(hashtable,num,tablesize)==-1){
				printf("null\n");
				break;
			}
			printf("%d\n", Find(hashtable, num, tablesize));
			break;

		/* print */
		case 'p':
			for(i=0; i<tablesize; i++)
				printf("%d\n", hashtable[i].table);
			break;

		/* quit */
		case 'q':
			return 0;
		}
	}
	return 0;
}