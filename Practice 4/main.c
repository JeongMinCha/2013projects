#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _tree {
	int value;
	struct _tree *left;
	struct _tree *right;
}Tree;

void insertNode(Tree * root, int);
Tree * findNode(Tree * root, int);
void printInorder(Tree * root);
void printPreorder(Tree * root);
void printPostorder(Tree * root);

int main()
{
	Tree *root = (Tree*)malloc(sizeof(Tree));
	char op;				/* operator */
	char checkOrder[10];	/* checking print order */
	int num;
	int quit = 0;			/* check quitting */

	root->left = NULL; root->right = NULL; root->value = NULL;

	while(quit != 1)
	{
		scanf("%c", &op);
		switch(op)
		{
			/* insert */
			case 'i' :
				scanf("%d", &num);
				insertNode(root, num);
				break;

			/* find */
			case 'f' :
				scanf("%d", &num);
				if(root->value == NULL)
				{
					printf("%d does not exist\n", num);
					break;
				}
				else
				{
					if(findNode(root, num)!=NULL)
					{
						printf("%d exists\n", num);
						break;
					}
					else
					{
						printf("%d does not exist\n", num);
						break;
					}
				}

			/* print */
			case 'p' :
				scanf("%s", checkOrder);

				if(!strcmp(checkOrder, "in"))
				{
					if(root->value == NULL)
						break;
					printf("inorder : ");
					printInorder(root);
					printf("\n");
				}
				else if(!strcmp(checkOrder, "pre"))
				{
					if(root->value == NULL)
						break;
					printf("preorder : ");
					printPreorder(root);
					printf("\n");
				}
				else if(!strcmp(checkOrder, "post"))
				{
					if(root->value == NULL)
						break;
					printf("postorder : ");
					printPostorder(root);
					printf("\n");
				}
				break;


			case 'q' :
				quit = 1;
				break;
		}

	}
}

void insertNode(Tree *root, int key)
{
	Tree *newNode = (Tree*)malloc(sizeof(Tree));
	newNode->value = NULL; newNode->left = NULL; newNode->right = NULL;
	newNode->value = key;

	if(root->value == NULL)
	{
		root->value = key;
		return;
	}

	if(findNode(root, key)!=NULL)
		return;

	if(root->value > key)
	{
		if(root->left == NULL)
			root->left = newNode;

		insertNode(root->left, key);
	}
	else
	{
		if(root->right == NULL)
			root->right = newNode;

		insertNode(root->right, key);
	}
}

Tree * findNode(Tree *root, int key)
{
	while(1)
	{
		if(root->value == key)
			return root;

		else if(root->value > key)
		{
			if(root->left == NULL)
				return NULL;
		
			root = root->left;
		}
		else
		{
			if(root->right == NULL)
				return NULL;
			
			root = root->right;
		}
	}
}

void printInorder(Tree * root)
{
	if(root == NULL)
		return;

	printInorder(root->left);
	printf("%d ", root->value);
	printInorder(root->right);
}

void printPreorder(Tree * root)
{
	if(root == NULL)
		return;

	printf("%d ", root->value);
	printPreorder(root->left);
	printPreorder(root->right);
}

void printPostorder(Tree * root)
{
	if(root == NULL)
		return;

	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ", root->value);
}


