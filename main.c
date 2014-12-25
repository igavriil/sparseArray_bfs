#include<stdio.h>
#include<stdlib.h>
#include "sparseArray.h"
#include "vertexLinkedList.h"
#include "edgeLinkedList.h"

void makeBfsTree(struct graphVertex* vertexesGroup, struct matrix* sparseArray);
struct graphVertex* vertexToBeExplored(struct graphVertex* graphVertexExplored);
struct graphVertex* findNextNeighbor(struct graphVertex* inputVertex,struct matrix* sparseArray);


main()
{
	struct matrix* graphSparseArray;
	graphSparseArray = sparseMenu();



	struct graphVertex* vertexesGroup = NULL;
	vertexesGroup= findGraphVertexes(vertexesGroup,graphSparseArray);

	printVertexList(vertexesGroup);

	int size = graphVertexSize(vertexesGroup);
	printf("size is: %d \n",size);

	
	makeBfsTree(vertexesGroup, graphSparseArray);
}

void makeBfsTree(struct graphVertex* vertexesGroup, struct matrix* sparseArray)
{

	struct graphVertex* graphVertexExplored = NULL;
	struct graphEdge* graphEdges = NULL;

	int rootVertex;
	printf("Give me the vertex for root\n");
	scanf("%d", &rootVertex);


	//allocate new graphvertex
	struct graphVertex* inputVertex = (struct graphVertex*)malloc(sizeof(struct graphVertex));
	//insert value for graphVertex
	inputVertex -> value = rootVertex;

	while( !vertexExists(inputVertex,vertexesGroup))
	{
		printf("Give me the vertex for root\n");
		scanf("%d", &rootVertex);
		inputVertex -> value = rootVertex;
	}
	//insert the inputVertex to the graphVertexEpxlored List
	graphVertexExplored = insertGraphVertex(inputVertex,graphVertexExplored);

//graphVertexSize(graphVertexExplored) != graphVertexSize(vertexesGroup)
	
	while(graphVertexSize(graphVertexExplored) != graphVertexSize(vertexesGroup))
	{
		//find the vertex to explore now
		struct graphVertex* exploringNow = vertexToBeExplored(graphVertexExplored); 
		
		printf("next vertex to explore: %d\n",exploringNow->value );

		printf("neighboors:\n");
		
		//find neighboors of exploringNow
		struct graphNode* aux = sparseArray->horizontalArray[exploringNow->value-1];
		while(aux -> right != NULL)
		{
			printf("%d\n",aux->right ->j);
			
			aux = aux->right;
			struct graphVertex* neighbor = (struct graphVertex*)malloc(sizeof(struct graphVertex));
			neighbor -> value = aux ->j;
			neighbor -> parent = exploringNow;
			neighbor -> visited = 0;


			struct graphEdge* inputEdge = (struct graphEdge*)malloc(sizeof(struct graphEdge));
			inputEdge -> i = exploringNow -> value;
			inputEdge -> j = neighbor -> value;

			if( vertexExists(neighbor,graphVertexExplored) )
			{
				inputEdge -> active = 0;
			}
			else
			{
				inputEdge -> active = 1;
			}


			if( !vertexExists(neighbor,graphVertexExplored))
			{
				graphVertexExplored = insertGraphVertex(neighbor,graphVertexExplored);
			}
			graphEdges = insertGraphEdge(inputEdge,graphEdges);

			

		}
		setVertexVisited(exploringNow,graphVertexExplored);
	}
	printVertexList(graphVertexExplored);
	printEdgeList(graphEdges);

}


struct graphVertex* vertexToBeExplored(struct graphVertex* graphVertexExplored)
{
	
	struct graphVertex* aux = graphVertexExplored;
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