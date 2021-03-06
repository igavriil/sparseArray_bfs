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
		if(aux->value == inputVertex->value)
		{
			aux -> visited = 1;
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

struct graphVertex* findVertexByValue(int value,struct graphVertex* aux)
{
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			if(aux->value == value)
			{
				break;
			}
			else
			{
				aux = aux->right;
			}
		}
	}
	return aux;
}

void printVertexList(struct graphVertex* aux)
{
	if(aux == NULL)
	{
		return;
	}
	printf("Vertex: %02d , Parent: %02d, Visited: %d\n", aux->value, aux->parent->value, aux->visited);

	printVertexList(aux->right);
}

int lastVertexVisited(struct graphVertex* aux)
{
	int visited = 0;
	if(aux != NULL)
	{
		while(aux->right != NULL)
		{
			aux = aux->right;
		}
		if(aux->visited == 1)
		{
			visited = 1;
		}
	}
	return visited;
}

struct graphVertex* vertexToBeExplored(struct graphVertex* aux)
{
	
	if(aux->right == NULL && aux -> visited == 0)
	{
		return aux;
	}
	else{
		while(aux -> right != NULL)
		{
			aux = aux->right;
			
			if(aux->visited == 0)
			{
				return aux;
			}
		}
	}
}

int relativeVertexes(struct graphVertex* LeafA,struct graphVertex* LeafB,struct graphVertex* graphVertexExplored)
{
	int relatives = 0;
	struct graphVertex* tempA =findVertexByValue(LeafA->value,graphVertexExplored);
	struct graphVertex* tempB =findVertexByValue(LeafB->value,graphVertexExplored);

	if(tempA->parent == tempB || tempB -> parent == tempA)
	{
		relatives = 1;
	}
	printf("These vertices are Relatives %d\n",relatives );

	return relatives;
}