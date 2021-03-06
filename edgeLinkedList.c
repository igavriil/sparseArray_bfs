#include<stdio.h>
#include<stdlib.h>
#include "edgeLinkedList.h"

struct graphEdge* insertGraphEdge(struct graphEdge* inputEdge,struct graphEdge* aux)
{
	struct graphEdge* head = aux;
	if(aux != NULL)
	{
		
		if(aux->right != NULL)
		{
			insertGraphEdge(inputEdge,aux->right);			
		}	
		else 
		{
			inputEdge -> right = aux ->right;
			inputEdge -> left = aux;
			aux -> right = inputEdge;
		}
	}
	else 
	{
		head = inputEdge;
	}
	return head;
}

void printEdgeList(struct graphEdge* aux)
{
	if(aux == NULL)
	{
		return;
	}
	printf("parent: %02d , child: %02d , active: %d \n", aux->i,aux->j, aux->active);

	printEdgeList(aux->right);
}

int deactivatedEdgeExists(struct graphEdge* inputEdge,struct graphEdge* aux)
{
	int exists = 0;
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			if(aux->i == inputEdge->i && aux->j == inputEdge->j) 
			{
				if(aux->active == 0)
				{
					exists = 1;
				}
				break;
			}
			else
			{
				aux = aux->right;
			}
		}
		if(aux->i == inputEdge->i && aux->j == inputEdge->j)
		{
			if(aux->active == 0)
			{
				exists = 1;
			}
		}
	}
	return exists;
}

int activatedEdgeExists(struct graphEdge* inputEdge,struct graphEdge* aux)
{
	int exists = 0;
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			if(aux->i == inputEdge->i && aux->j == inputEdge->j) 
			{
				if(aux->active == 1)
				{
					exists = 1;
				}
				break;
			}
			else
			{
				aux = aux->right;
			}
		}
		if(aux->i == inputEdge->i && aux->j == inputEdge->j)
		{
			if(aux->active == 1)
			{
				exists = 1;
			}
		}
	}
	return exists;
}

