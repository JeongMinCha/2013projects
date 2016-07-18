#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tree Node structure */
typedef struct Tree
{
	int value;
	struct Tree * left;
	struct Tree * right;
} Tree;

/* function type */
void insertNode(Tree * root, int key);
Tree * findNode(Tree * root, int key);
void printInorder(Tree * root);
void printPreorder(Tree * root);
void printPostorder(Tree * root);
void deleteNode(Tree * root, int key);
Tree * findpreNode(Tree * root, int key);

int main(void)
{
	Tree * root = (Tree*)malloc(sizeof(Tree));			// The root of the tree.
	char checkOrder[5];	/* checking the print order */
	char op = '0'; /* operator */
	int num = 0;
	int quit = 0; /* checking quitting */

	/* Initialization of "root" */
	root->left = NULL;
	root->right = NULL;
	root->value = NULL;

	while(quit != 1)
	{
		scanf("%c", &op);

		switch(op)
		{
		case 'i':
			scanf("%d", &num);
			insertNode(root, num);
			break;

		case 'f':
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

		case 'p':
			scanf("%s", checkOrder);
			if(!strcmp(checkOrder, "in")){
				if(root->value == NULL)
					break;
				printf("inorder : ");
				printInorder(root);
				printf("\n");
			}
			else if(!strcmp(checkOrder, "pre")){
				if(root->value == NULL)
					break;
				printf("preorder : ");
				printPreorder(root);
				printf("\n");
			}
			else if(!strcmp(checkOrder, "post")){
				if(root->value == NULL)
					break;
				printf("postorder : ");
				printPostorder(root);
				printf("\n");
			}
			break;

		case 'd':
			scanf("%d", &num);
			deleteNode(root, num);
			break;

		case 'q':
			quit = 1;
			break;
		}

	}

	return 0;
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

void deleteNode(Tree *root, int key)
{
	Tree *pre = findpreNode(root, key);
	Tree *delNode;
	Tree *tmp;
	Tree *delNodeleft;

	if(pre==NULL)
		return;

	if((pre->left != NULL)&&(pre->left->value == key))
	{
		delNode = pre->left;
		if(delNode->left == NULL){
			tmp = delNode->right;
			free(delNode);
			pre->left = tmp;
			return;
		}
		else if(delNode->right == NULL){
			tmp = delNode->left;
			free(delNode);
			pre->left = tmp;
			return;
		}
		else{
			tmp = delNode;
			if(tmp->left->right != NULL)
			{
				tmp = tmp->left;
				while(tmp->right->right != NULL)
				{
					tmp = tmp->right;
				}
				delNode = tmp->right;
				pre->left->value = delNode->value;
				delNodeleft = delNode->left;
				free(delNode);
				tmp->right = delNodeleft;
				return;
			}
			else
			{
				delNode = tmp->left;
				pre->left->value = delNode->value;
				delNodeleft = delNode->left;
				free(delNode);
				tmp->left = delNodeleft;
				return;
			}
		}
	}
	else
	{
		delNode = pre->right;
		if(delNode->left == NULL){
			tmp = delNode->right;
			free(delNode);
			pre->right = tmp;
			return;
		}
		else if(delNode->right == NULL){
			tmp = delNode->left;
			free(delNode);
			pre->right = tmp;
			return;
		}
		else{
			tmp = delNode;
			if(tmp->left->right != NULL){
				tmp = tmp->left;
				while(tmp->right->right != NULL){
					tmp = tmp->right;
				}
				delNode = tmp->right;
				pre->right->value = delNode->value;
				delNodeleft = delNode->left;
				free(delNode);
				tmp->right = delNodeleft;
				return;
			}
			else{
				delNode = tmp->left;
				pre->right->value = delNode->value;
				delNodeleft = delNode->left;
				free(delNode);
				tmp->left = delNodeleft;
				return;
			}
		}
	}

}

/* The function which returns the pre-level of parameter Tree Pointer "root". */
Tree * findpreNode(Tree * root, int key)
{
	if(key < root->value)
	{
		if(root->left == NULL)
			return NULL;
		else if(root->left->value == key)
			return root;
		else
			return findpreNode(root->left, key);
	}
	else
	{
		if(root->right == NULL)
			return NULL;
		else if(root->right->value == key)
			return root;
		else
			return findpreNode(root->right, key);
	}
}
