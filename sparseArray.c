#include<stdio.h>
#include<stdlib.h>
#include "sparseArray.h"
#include "vertexLinkedList.h"
#include "edgeLinkedList.h"

struct matrix* sparseMenu()
{
	struct graphVertex* vertexesGroup = NULL;
	
	int sparseArraySize;
	printf("Welcome! Give me the size of the Sparse Array\n");
	scanf("%d",&sparseArraySize);
	getchar();
	struct matrix* sparseArray = headConstruct(sparseArraySize);
	printf("Sparse Array with linked lists\n");
	printf("------------------------------\n");

	char choise;
	int value;

	//vertexesGroup= findGraphVertexes(vertexesGroup,sparseArray);

	do
	{
		printf("Press i(insert from file), e(edit with hand) p(printGraph), d(delete), n(find vertex neighboors), q(quit)\n");
		scanf("%c", &choise);
		getchar();
		switch(choise)
		{
			case 'i':
				readFromFile(sparseArray);
				break;
			case 'e':
				insertByHand(sparseArray);
				break;
			case 'p':
				printGraph(sparseArray);
				break;
			case 'd':
				delete(sparseArray);
				break;
			case 'q':
				printf("Goodbye\n");
				break;
			default:
				printf("Wrong Selection\n");
		}
	}
	while(choise != 'q');

	return sparseArray;
}

struct graphVertex* findGraphVertexes(struct graphVertex* vertexesGroup,struct matrix* sparseArray)
{
	int k;
	for(k=0;k<(sparseArray -> size);k++)
	{
		struct graphNode* aux = sparseArray->horizontalArray[k];
		if(aux -> right != NULL)
		{	
			struct graphVertex* temp = (struct graphVertex*)malloc(sizeof(struct graphVertex));
			temp -> value = aux->right->i;
			temp -> parent = NULL;
			temp -> visited = 0;
			vertexesGroup = insertGraphVertex(temp,vertexesGroup);	
		}
	}
	return vertexesGroup;
}
/*moved to BFS main
void findVertexNeighboors(struct graphVertex* vertexesGroup, struct matrix* sparseArray)
{
	int value;
	struct graphVertex* temp = (struct graphVertex*)malloc(sizeof(struct graphVertex));

	printf("Insert Vertex value\n");
	scanf("%d",&temp->value);
	getchar();
	
	int exists = vertexExists(temp,vertexesGroup);
	if(exists)
	{
		printf("Vertex exists\n");
	}
	else
	{
		printf("Vertex does not exists\n");
		return;
	}
	
	struct graphNode* aux = sparseArray->horizontalArray[temp->value-1];
	printf("neighboors:\n");
	while( aux -> right != NULL)
	{	
		printf("%d\n",aux->right ->j);
		aux = aux->right;
	}
}*/


struct matrix* headConstruct(int size)
{
	struct matrix* sparseArray  = malloc(sizeof(struct matrix));
	sparseArray -> size = size;
	sparseArray -> horizontalArray = malloc((sparseArray -> size)*sizeof(struct graphNode*));
	sparseArray -> verticalArray = malloc((sparseArray -> size)*sizeof(struct graphNode*));

	int k;
	for(k=0;k<(sparseArray -> size);k++)
	{
		struct graphNode* horizontaltemp = (struct graphNode*)malloc(sizeof(struct graphNode));
		horizontaltemp -> i = k+1;
		horizontaltemp -> j = 0;
		sparseArray->horizontalArray[k] = horizontaltemp;
		
		struct graphNode* verticaltemp = (struct graphNode*)malloc(sizeof(struct graphNode));
		verticaltemp -> i = 0;
		verticaltemp -> j = k+1;
		sparseArray->verticalArray[k] = verticaltemp;
	}
	return sparseArray;
}

int graphNodeExists(struct matrix* sparseArray,struct graphNode* inputgraphNode)
{
	int exists = 0;
	struct graphNode* horizontalAux;
	struct graphNode* verticalAux;

	horizontalAux= sparseArray -> horizontalArray[(inputgraphNode -> i)-1];
	if(horizontalAux->right != NULL)
	{
		while(horizontalAux -> right -> j <= inputgraphNode ->j  && horizontalAux->right != NULL)
		{
			printf("moving right\n");
			
			horizontalAux = horizontalAux->right;
			if(horizontalAux->j == inputgraphNode ->j)
			{
				exists += 1;
			}
			if(horizontalAux -> right == NULL)
			{
				printf("carefull the is no one right need to stop moving\n");
				break;
			}			
		}
	}
		
	verticalAux= sparseArray -> verticalArray[(inputgraphNode -> j)-1];
	if(verticalAux->down != NULL)
	{
		while(verticalAux -> down -> i <= inputgraphNode ->i  && verticalAux->down != NULL)
		{
			printf("moving down\n");
			
			verticalAux = verticalAux->down;
			if(verticalAux->i == inputgraphNode->i)
			{
				exists += 1;
			}
			if(verticalAux -> down == NULL)
			{
				printf("carefull the is no one down need to stop moving\n");
				break;
			}	
		}
	}

	if(exists == 2)
	{
		return 1;
	}
	else 
	{
		return 0;	
	}
}


void printGraph(struct matrix* sparseArray)
{
	int k;
	printf("   ");

	for(k=0;k<(sparseArray -> size);k++)
	{
		printf("|%02d|",k+1);
	}
	printf("\n");
	printf("____");
	for(k=0;k<(sparseArray -> size);k++)
	{
		printf("____");
	}
	printf("\n");
	
	for(k=0;k<(sparseArray -> size);k++)
	{
		printf("%02d ",k+1);
		struct graphNode* aux = sparseArray->horizontalArray[k];
		while( aux -> right != NULL)
		{	
			int i;
			for(i=1; i< ( aux ->right->j - aux->j); i++)
			{
				printf("|--|");
			}
			printf("|%02d|",aux->right ->data);
			aux = aux->right;
		}
		int i;
		for(i=0; i< (sparseArray -> size) - aux->j;i++)
		{
			printf("|--|");
		}
		printf("\n");
	}
	printf("________________________\n");
}

void insertByHand(struct matrix* sparseArray)
{
	printf("Insert pair (i,j) for graphNode\n");
	struct graphNode* temp = (struct graphNode*)malloc(sizeof(struct graphNode));
	scanf("%d %d",&temp->i, &temp->j);
	getchar();
	printf("Insert data for graphNode\n");
	scanf("%d", &temp->data);
	getchar();

	insert(sparseArray,temp);
}

void insert(struct matrix* sparseArray,struct graphNode* input)
{
	struct graphNode* temp = (struct graphNode*)malloc(sizeof(struct graphNode));
	temp->i = input->i;
	temp->j = input->j;
	temp -> data = input->data;

	struct graphNode* invtemp = (struct graphNode*)malloc(sizeof(struct graphNode));
	invtemp->i = input->j;
	invtemp->j = input->i;
	invtemp->data = input->data;
	if(!graphNodeExists(sparseArray,temp))
	{
		struct graphNode* horizontalAux = sparseArray -> horizontalArray[(temp -> i)-1];
		horizontalInsert(horizontalAux,temp);

		struct graphNode* verticalAux = sparseArray -> verticalArray[(temp -> j)-1];
		verticalInsert(verticalAux,temp);
	}
	else
	{
		printf("graphNode exists\n");	
	}
	if(!graphNodeExists(sparseArray,invtemp))
	{
		struct graphNode* horizontalAux = sparseArray -> horizontalArray[(invtemp -> i)-1];
		horizontalInsert(horizontalAux,invtemp);

		struct graphNode* verticalAux = sparseArray -> verticalArray[(invtemp -> j)-1];
		verticalInsert(verticalAux,invtemp);
	}
	else
	{
		printf("graphNode exists\n");	
	}
}
void delete(struct matrix* sparseArray)
{
	printf("Insert pair (i,j) for graphNode\n");
	struct graphNode* temp = (struct graphNode*)malloc(sizeof(struct graphNode));
	scanf("%d", &temp->i);
	getchar();
	scanf("%d", &temp->j);
	getchar();
	
	if(graphNodeExists(sparseArray,temp))
	{
		struct graphNode* horizontalAux = sparseArray -> horizontalArray[(temp -> i)-1];
		horizontalDelete(horizontalAux,temp);

		struct graphNode* verticalAux = sparseArray -> verticalArray[(temp -> j)-1];
		verticalDelete(verticalAux,temp);
	}
	else
	{
		printf("graphNode does not exists\n");
	}
}

void horizontalInsert(struct graphNode* horizontalAux, struct graphNode* inputgraphNode)
{
	if(horizontalAux -> right == NULL)
	{
		printf("I am the first one on this line\n");
		inputgraphNode -> left = horizontalAux;
		horizontalAux -> right = inputgraphNode;
	}
	else
	{
		
		printf("Someone is already in this line. Trying to find my place\n");

		while(horizontalAux -> right -> j < inputgraphNode ->j  && horizontalAux->right != NULL)
		{
			printf("moving right\n");
			
			horizontalAux = horizontalAux->right;
			if(horizontalAux -> right == NULL)
			{
				printf("carefull the is no one right need to stop moving\n");
				break;
			}				
		}
		if(horizontalAux->right == NULL)
		{
			printf("I am the last one in this line.\n");
			inputgraphNode -> right = horizontalAux ->right;
			inputgraphNode -> left = horizontalAux;
			horizontalAux -> right = inputgraphNode;
	 	}
		else
		{
			printf("I am between other graphNodes in this line.\n");
			inputgraphNode -> right = horizontalAux -> right;
			inputgraphNode -> left = horizontalAux;
			horizontalAux -> right -> left = inputgraphNode;
			horizontalAux -> right = inputgraphNode;
		}
	}
}
void verticalInsert(struct graphNode* verticalAux, struct graphNode* inputgraphNode)
{
	if(verticalAux -> down == NULL)
	{
		printf("I am the first one on this row\n");
		inputgraphNode -> up = verticalAux;
		verticalAux -> down = inputgraphNode;
	}
	else
	{
		
		printf("Someone is already in this row. Trying to find my place\n");

		while(verticalAux -> down -> i < inputgraphNode ->i  && verticalAux->down != NULL)
		{
			printf("moving down\n");
			
			verticalAux = verticalAux->down;
			if(verticalAux -> down == NULL)
			{
				printf("carefull the is no one down need to stop moving\n");
				break;
			}				
		}
		if(verticalAux->down == NULL)
		{
			printf("I am the last one in this row.\n");
			inputgraphNode -> down = verticalAux ->down;
			inputgraphNode -> up = verticalAux;
			verticalAux -> down = inputgraphNode;
	 	}
		else
		{
			printf("I am between other graphNodes in this row.\n");
			inputgraphNode -> down = verticalAux -> down;
			inputgraphNode -> up = verticalAux;
			verticalAux -> down -> up = inputgraphNode;
			verticalAux -> down = inputgraphNode;
		}
	}
}

void horizontalDelete(struct graphNode* horizontalAux, struct graphNode* inputgraphNode)
{
	if(horizontalAux -> right == NULL)
	{
		printf("This line is empty. Nothing to delete\n");
	}
	else
	{
		printf("Someone is in this line. Trying to find the one to be deleted\n");

		while(horizontalAux -> right -> j <= inputgraphNode ->j  && horizontalAux->right != NULL)
		{
			printf("moving right\n");
			horizontalAux = horizontalAux->right;
			if(horizontalAux -> right == NULL)
			{
				printf("carefull the is no one right need to stop moving\n");
				break;
			}
		}
		if(horizontalAux->right == NULL && horizontalAux->j == inputgraphNode->j)
		{
			printf("I am the last one in this line and i need to be deleted.\n");
			horizontalAux -> left ->right = horizontalAux ->right;	
		}
		else if(horizontalAux->j == inputgraphNode->j)
		{
			printf("I am between other graphNodes in this line and i need to be deleted.\n");
			horizontalAux -> left ->right = horizontalAux -> right;
			horizontalAux -> right -> left = horizontalAux -> left;
		}
	}
}

void verticalDelete(struct graphNode* verticalAux, struct graphNode* inputgraphNode)
{
	if(verticalAux -> down == NULL)
	{
		printf("This row is empty. Nothing to delete\n");
	}
	else
	{
		
		printf("Someone is in this row. Trying to find the one to be deleted\n");

		while(verticalAux -> down -> i <= inputgraphNode ->i  && verticalAux->down != NULL)
		{
			printf("moving down\n");
			verticalAux = verticalAux->down;
			if(verticalAux -> down == NULL)
			{
				printf("carefull the is no one down need to stop moving\n");
				break;
			}			
		}
		if(verticalAux->down == NULL && verticalAux->i == inputgraphNode->i)
		{
			printf("I am the last one in this row and i need to be deleted.\n");
			verticalAux -> up ->down = verticalAux ->down;
	 	}
		else if(verticalAux->i == inputgraphNode->i)
		{
			printf("I am between other graphNodes in this line and i need to be deleted.\n");
			verticalAux -> up ->down = verticalAux -> down;
			verticalAux -> down -> up = verticalAux -> up;
		}
	}
}

void readFromFile(struct matrix* sparseArray)
{
	printf("reading file\n");
	int i,j,data;
	FILE *fp;
	fp = fopen("/home/tsou/Desktop/structures_new/sparseArray/sparse.txt","r");

	if(fp == NULL)
	{
		printf("Error opening the file\n");
		exit(-1);
	}
	while(fscanf(fp,"%d%d%d",&i,&j,&data) != EOF)
	{
		printf("%d %d %d\n",i,j,data);
		struct graphNode* temp = (struct graphNode*)malloc(sizeof(struct graphNode));
		temp -> i = i;
		temp -> j = j;
		temp -> data = data;
		insert(sparseArray,temp);
	}
	fclose(fp);
}
/*void checkExists(struct matrix* sparseArray)
{
	printf("Insert pair (i,j) for graphNode\n");
	struct graphNode* temp = (struct graphNode*)malloc(sizeof(struct graphNode));
	scanf("%d %d",&temp->i, &temp->j);
	getchar();
	int exists = graphNodeExists(sparseArray,temp);
	char choise;


	if(exists)
	{
		printf("graphNode exists\n");
		
		printf("Press u(update)\n");
		scanf("%c", &choise);
		getchar();
		switch(choise)
		{
			case 'u':
				printf("Insert new data for graphNode\n");
				scanf("%d", &temp->data);
				getchar();	
				graphNodeUpdate(sparseArray,temp);
				break;
			default:
				printf("Continue without update\n");		
		}
	}
	else
	{
		printf("graphNode does not exists\n");
	}

}

void graphNodeUpdate(struct matrix* sparseArray,struct graphNode* inputgraphNode)
{

	struct graphNode* aux;

	aux = sparseArray -> horizontalArray[(inputgraphNode -> i)-1];
	if(aux->right != NULL)
	{
		while(aux -> right -> j <= inputgraphNode ->j  && aux->right != NULL)
		{
			printf("moving right\n");
			
			aux = aux->right;
			if(aux->j == inputgraphNode ->j)
			{
				aux->data = inputgraphNode->data;
				break;
			}
		}
	}
	aux = sparseArray -> verticalArray[(inputgraphNode -> j)-1];
	if(aux->down != NULL)
	{
		while(aux -> down -> i <= inputgraphNode ->i  && aux->down != NULL)
		{
			printf("moving down\n");
			
			aux = aux->down;
			if(aux->i == inputgraphNode->i)
			{
				aux -> data = inputgraphNode -> data;
				break;
			}
		}
	}
}


void findgraphNodesByValue(struct matrix* sparseArray,int data)
{
	int k;
	for(k=0;k<(sparseArray -> size);k++)
	{
		struct graphNode* aux = sparseArray->horizontalArray[k];
		while( aux -> right != NULL)
		{	
			aux = aux->right;
			if(aux->data == data)
			{
				printf("found on (%d,%d)\n",aux->i,aux->j);
			}
		}
	}
}*/
