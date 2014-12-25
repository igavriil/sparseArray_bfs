#include<stdio.h>
#include<stdlib.h>
#include "pathToRootList.h"

struct treeEdge* insertTreeEdge(struct treeEdge* inputEdge,struct treeEdge* aux)
{
	struct treeEdge* head = aux;
	if(aux != NULL)
	{
		inputEdge -> right = aux;
		aux -> left = inputEdge;
		head = inputEdge;
	}
	else 
	{
		head = inputEdge;
	}
	return head;
}

void printTreeEdgeList(struct treeEdge* aux)
{
	if(aux == NULL)
	{
		return;
	}
	printf("parent: %02d , child: %02d \n", aux->i,aux->j);

	printTreeEdgeList(aux->right);
}


struct treeEdge* mergePaths(struct treeEdge* pathA,struct treeEdge* pathB)
{
	struct treeEdge* pathUnion = NULL;
	struct treeEdge* auxA = pathA;
	struct treeEdge* auxB = pathB;
	struct treeEdge* temp;
	while(auxA -> i == auxB -> i && auxA -> j == auxB -> j)
	{
		printf("Edge in Common\n");
		if(auxA -> right == NULL || auxB -> right == NULL)
		{
			break;
		}
		auxA= auxA -> right;
		auxB= auxB -> right;
	}
	if(auxA == auxB)
	{
		printf("What is happenning\n");
	}
	if(auxA != NULL)
	{
		while(auxA->right!=NULL)
		{
			temp = createTreeEdgeCopy(auxA);
			pathUnion = insertTreeEdge(temp,pathUnion);
			auxA = auxA -> right;
		}
		temp = createTreeEdgeCopy(auxA);
		pathUnion = insertTreeEdge(temp,pathUnion);
	}
	printf("Inserted all pathA edges\n");

	if(auxB != NULL)
	{
		while(auxB->right!=NULL)
		{
			temp = createTreeEdgeCopy(auxB);
			pathUnion = insertTreeEdge(temp,pathUnion);
			auxB = auxB -> right;
		}
		temp = createTreeEdgeCopy(auxB);
		pathUnion = insertTreeEdge(temp,pathUnion);
	}
	printf("Inserted all pathB edges\n");

	return pathUnion;
}

struct treeEdge* createTreeEdgeCopy(struct treeEdge* inputEdge)
{
	struct treeEdge* outputEdge = (struct treeEdge*)malloc(sizeof(struct treeEdge));
	outputEdge -> i = inputEdge -> i;
	outputEdge -> j = inputEdge -> j;
}
