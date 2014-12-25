#include<stdio.h>
#include<stdlib.h>
#include "sparseArray.h"
#include "vertexLinkedList.h"
#include "edgeLinkedList.h"
#include "pathToRootList.h"

void makeBfsTree(struct graphVertex* vertexesGroup, struct matrix* sparseArray);
struct graphVertex* findNextNeighbor(struct graphVertex* inputVertex,struct matrix* sparseArray);
struct treeEdge* fromVertexToRoot(struct graphVertex* Leaf, struct graphVertex* graphVertexExplored);
void findCycles(void);

struct graphVertex* graphVertexExplored = NULL;
struct graphEdge* graphEdges = NULL;

main()
{
	struct matrix* graphSparseArray;
	graphSparseArray = sparseMenu();

	struct graphVertex* vertexesGroup = NULL;
	vertexesGroup= findGraphVertexes(vertexesGroup,graphSparseArray);

	int size = graphVertexSize(vertexesGroup);
	printf("size is: %d \n",size);

	makeBfsTree(vertexesGroup, graphSparseArray);

	printf("--------------Vertices-------------\n");
	printVertexList(graphVertexExplored);
	printf("---------------Edges---------------\n");
	printEdgeList(graphEdges);

	char choise;
	do
	{
		printf("Press f(find cycles), q(quit)\n");
		scanf("%c", &choise);
		getchar();
		switch(choise)
		{
			case 'f':
				findCycles();
				break;
			case 'q':
				printf("Goodbye\n");
				break;
			default:
				printf("Wrong Selection\n");
		}
	}
	while(choise != 'q');
}

void makeBfsTree(struct graphVertex* vertexesGroup, struct matrix* sparseArray)
{
	int rootVertex;

	//allocate new graphvertex
	struct graphVertex* inputVertex = (struct graphVertex*)malloc(sizeof(struct graphVertex));
	while( !vertexExists(inputVertex,vertexesGroup))
	{
		printf("Give me the vertex for root\n");
		scanf("%d", &rootVertex);
		getchar();
		inputVertex -> value = rootVertex;
		inputVertex -> visited = 0;
		inputVertex -> parent = inputVertex;
	}
	//insert the inputVertex to the graphVertexEpxlored List
	graphVertexExplored = insertGraphVertex(inputVertex,graphVertexExplored);
	
	//while(graphVertexSize(graphVertexExplored) != graphVertexSize(vertexesGroup))
	while(!lastVertexVisited(graphVertexExplored))
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
}

void findCycles(void)
{
	
	struct graphEdge* temp = (struct graphEdge*)malloc(sizeof(struct graphEdge));
	struct graphVertex* LeafA = (struct graphVertex*)malloc(sizeof(struct graphVertex));
	struct graphVertex* LeafB = (struct graphVertex*)malloc(sizeof(struct graphVertex));
	
	while(!deactivatedEdgeExists(temp,graphEdges) || relativeVertexes(LeafA,LeafB,graphVertexExplored))
	{
		printf("Give me a deactivated Edge (i,j)\n");
		scanf("%d %d",&temp->i, &temp->j);
		getchar();

		LeafA -> value = temp -> i;
		LeafB -> value = temp -> j;
	}

	struct treeEdge* pathToRootA = NULL;
	struct treeEdge* pathToRootB = NULL;

	pathToRootA = fromVertexToRoot(LeafA,graphVertexExplored);
	printf("From Vertex A to Root Reverse Print\n");
	printTreeEdgeList(pathToRootA);
	
	pathToRootB = fromVertexToRoot(LeafB,graphVertexExplored);
	printf("From Vertex B to Root Reverse Print\n");
	printTreeEdgeList(pathToRootB);

	struct treeEdge* pathUnion = NULL;
	struct treeEdge* inCommon = (struct treeEdge*)malloc(sizeof(struct treeEdge));
	inCommon -> i = temp -> i;
	inCommon -> j = temp -> j;
	pathUnion = mergePaths(pathToRootA,pathToRootB);
	pathUnion = insertTreeEdge(inCommon,pathUnion);
	printf("Circle\n");
	printTreeEdgeList(pathUnion);

}


struct treeEdge* fromVertexToRoot(struct graphVertex* Leaf, struct graphVertex* graphVertexExplored)
{
	struct treeEdge* pathToRoot = NULL;
	
	struct graphVertex* aux;
	if(vertexExists(Leaf,graphVertexExplored))
	{
		aux = findVertexByValue(Leaf -> value,graphVertexExplored);
	}
	while(aux->parent != aux)
	{
		struct treeEdge* inputTreeEdge= (struct treeEdge*)malloc(sizeof(struct treeEdge));
		inputTreeEdge ->j = aux-> value;
		inputTreeEdge ->i = aux->parent->value;
		pathToRoot =  insertTreeEdge(inputTreeEdge,pathToRoot);
		aux = aux-> parent;
	}
	struct treeEdge* inputTreeEdge= (struct treeEdge*)malloc(sizeof(struct treeEdge));
	inputTreeEdge ->j = aux-> value;
	inputTreeEdge ->i = aux->parent->value;
	pathToRoot =  insertTreeEdge(inputTreeEdge,pathToRoot);
	return pathToRoot;
}

