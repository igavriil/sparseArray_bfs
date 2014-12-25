#include<stdio.h>
#include<stdlib.h>
#include "vertexLinkedList.h"

struct graphVertex* insertGraphVertex(struct graphVertex* inputVertex,struct graphVertex* aux)
{
	struct graphVertex* head = aux;
	if(aux != NULL)
	{
		
		if(aux->right != NULL)
		{
			insertGraphVertex(inputVertex,aux->right);			
		}	
		//insertgraphVertex at tail
		else if(inputVertex->value != aux -> value)
		{
			inputVertex -> right = aux ->right;
			inputVertex -> left = aux;
			aux -> right = inputVertex;
		}
	}
	else 
	{
		head = inputVertex;
	}
	return head;
}

void setVertexVisited(struct graphVertex* inputVertex,struct graphVertex* aux)
{
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			if(aux->value == inputVertex->value)
			{
				aux -> visited = 1;
				break;
			}
			else
			{
				aux = aux->right;
			}
		}
	}
}

int graphVertexSize(struct graphVertex* aux)
{
	int count =0;
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			count += 1;
			aux = aux -> right;
		}
	}
	count+=1;
	return count;
}

int vertexExists(struct graphVertex* inputVertex,struct graphVertex* aux)
{
	int exists = 0;
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			if(aux->value == inputVertex->value)
			{
				exists = 1;
				break;
			}
			else
			{
				aux = aux->right;
			}
		}
		if(aux->value == inputVertex->value)
		{
			exists = 1;
		}
	}
	return exists;
}

void printVertexList(struct graphVertex* aux)
{
	if(aux == NULL)
	{
		return;
	}
	printf("Vertex: %02d , Visited: %d\n", aux->value, aux->visited);

	printVertexList(aux->right);
}

